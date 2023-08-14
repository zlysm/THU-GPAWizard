#include "GradeManager.hpp"

GradeManager::GradeManager(std::vector<Student*>& students, std::vector<Course*>& courses)
    : _students(students), _courses(courses) {}

GradeManager::~GradeManager() {
    for (auto& student : _students)
        delete student;
    for (auto& course : _courses)
        delete course;
}

void GradeManager::studentSelectCourse() {
    for (auto& student : _students) {
        std::cout << "Student " << student->getName() << " select courses: " << std::endl;

        const std::string prompt = "Input course number to select(0 to finish): ";

        for (int courseNumber = IO::checkInput<int>(prompt); 0 != courseNumber;
             courseNumber = IO::checkInput<int>(prompt)) {
            bool selected = false;  // check if the course has already been selected
            for (const auto& course : student->_courses)
                if (course.number == courseNumber) {
                    selected = true;
                    std::cout << "Course " << course.name << " has already been selected." << std::endl;
                    break;
                }
            if (selected) continue;

            bool found = false;
            for (const auto& course : _courses)
                if (course->_number == courseNumber) {
                    found = true;
                    student->selectCourse(course->getCourseInfo());                   // push course to student
                    course->updateStudentList(student->getID(), student->getName());  // push student to course
                    std::cout << "Course " << course->_name << " selected." << std::endl
                              << std::endl;
                    break;
                }

            if (!found)
                std::cout << "Course not found." << std::endl;
        }
        std::cout << "Student " << student->getName() << " select courses finished." << std::endl
                  << std::endl;
    }
}

void GradeManager::teacherSetGrade() {
    for (auto& course : _courses)
        if (!course->_students.empty()) {
            const std::string prompt = "Do you want to see all " + std::to_string(course->_students.size()) +
                                       " students' info in " + course->_name + " course? (y/n)";
            char choice = IO::checkInput<char>(prompt);
            if ('n' != choice && 'N' != choice)
                for (const auto& courseStu : course->_students)  // for all students in this course
                    for (const auto& student : _students)        // fine the student in all students
                        if (student->getID() == courseStu.first) {
                            student->showInfo();
                            break;
                        }
            course->setGrade();
        }
}

void GradeManager::pushGrade() {
    for (const auto& course : _courses)                   // for all courses
        for (const auto& courseStu : course->_students)   // for all students in this course
            for (auto& student : _students)               // find the student in all students
                if (student->getID() == courseStu.first)  // push grade to student
                    student->_courseGrades[course->_number] = course->_students.at(courseStu.first).second;

    for (auto& student : _students)  // update all students' GPA
        student->calculateGPA();
}

bool GradeManager::pushGrade(int courseNumber) {
    for (const auto& course : _courses)  // find the course
        if (course->_number == courseNumber) {
            for (const auto& courseStu : course->_students)  // for all students in this course
                for (auto& student : _students)              // find the student in all students
                    if (student->getID() == courseStu.first) {
                        student->_courseGrades[courseNumber] = course->_students.at(courseStu.first).second;
                        student->calculateGPA();
                    }
            return true;
        }
    return false;
}

void GradeManager::saveStudents(SortType type) {
    auto students = _students;
    std::ofstream fout("shared/StudentsInfo.csv", std::ios::trunc);
    if (!fout.is_open()) {
        std::cerr << "Error opening file StudentsInfo.csv" << std::endl;
        exit(1);
    }

    switch (type) {
        case SortType::NAME:
            std::sort(students.begin(), students.end(), [](Student* a, Student* b) {
                return a->getName() < b->getName();
            });
            break;
        case SortType::NUMBER:
            std::sort(students.begin(), students.end(), [](Student* a, Student* b) {
                return a->getID() > b->getID();
            });
            break;
        case SortType::GRADE:
            std::sort(students.begin(), students.end(), [](Student* a, Student* b) {
                return a->getGPA() > b->getGPA();
            });
            break;
        case SortType::NONE:
        default:
            break;
    }

    fout << "Name,ID,Gender,Birth date,GPA" << std::endl;
    for (const auto& student : students)
        fout << student->getName() << "," << student->getID() << "," << student->getGender() << ","
             << student->getBirth() << "," << student->getGPA() << std::endl;

    fout.close();
    std::cout << "Successfully saved students info to StudentsInfo.csv" << std::endl;
}

bool GradeManager::saveStudents(int studentID, SortType type) {
    Student* student = nullptr;
    bool found = false;
    for (const auto& stu : _students)
        if (stu->getID() == studentID) {
            student = stu;
            found = true;
            break;
        }
    if (!found) return false;

    std::ofstream fout("shared/" + student->getName() + ".csv", std::ios::trunc);
    if (!fout.is_open()) {
        std::cerr << "Error opening file " << student->getName() << ".csv" << std::endl;
        exit(1);
    }

    std::vector<std::pair<CourseInfo, double>> courses;  // <course info, grade>
    courses.reserve(student->_courses.size());
    for (const auto& stuCourse : student->_courses)
        courses.emplace_back(stuCourse, student->_courseGrades.at(stuCourse.number));

    switch (type) {
        case SortType::NAME:
            std::sort(courses.begin(), courses.end(),
                      [](const std::pair<CourseInfo, double>& a, const std::pair<CourseInfo, double>& b) {
                          return a.first.name < b.first.name;
                      });
            break;
        case SortType::NUMBER:
            std::sort(courses.begin(), courses.end(),
                      [](const std::pair<CourseInfo, double>& a, const std::pair<CourseInfo, double>& b) {
                          return a.first.number > b.first.number;
                      });
            break;
        case SortType::GRADE:
            std::sort(courses.begin(), courses.end(),
                      [](const std::pair<CourseInfo, double>& a, const std::pair<CourseInfo, double>& b) {
                          return a.second > b.second;
                      });
            break;
        case SortType::NONE:
        default:
            break;
    }

    fout << "Name,Number,Credit,Grade,GPA" << std::endl;
    for (const auto& course : courses)
        fout << course.first.name << "," << course.first.number << "," << course.first.credits << ","
             << course.second << "," << Student::grade2GPA(course.second) << std::endl;

    fout.close();
    std::cout << "Successfully saved student " << student->getName() << "'s courses info to " << student->getName()
              << ".csv" << std::endl;
    return true;
}

bool GradeManager::saveCourses(int courseID, SortType type) {
    Course* course = nullptr;
    bool found = false;
    for (const auto& cou : _courses)
        if (cou->_number == courseID) {
            course = cou;
            found = true;
            break;
        }
    if (!found) return false;

    std::ofstream fout("shared/" + course->_name + ".csv", std::ios::trunc);
    if (!fout.is_open()) {
        std::cerr << "Error opening file " << course->_name << ".csv" << std::endl;
        exit(1);
    }

    std::vector<std::pair<int, StudentInfo>> students;  // <student id, student info>
    students.reserve(course->_students.size());
    for (const auto& stu : course->_students)
        students.emplace_back(stu.first, stu.second);

    switch (type) {
        case SortType::NAME:
            std::sort(students.begin(), students.end(),
                      [](const std::pair<int, StudentInfo>& a, const std::pair<int, StudentInfo>& b) {
                          return a.second.first < b.second.first;
                      });
            break;
        case SortType::NUMBER:
            std::sort(students.begin(), students.end(),
                      [](const std::pair<int, StudentInfo>& a, const std::pair<int, StudentInfo>& b) {
                          return a.first > b.first;
                      });
            break;
        case SortType::GRADE:
            std::sort(students.begin(), students.end(),
                      [](const std::pair<int, StudentInfo>& a, const std::pair<int, StudentInfo>& b) {
                          return a.second.second > b.second.second;
                      });
            break;
        case SortType::NONE:
        default:
            break;
    }

    fout << "Name,ID,Grade,GPA" << std::endl;
    for (const auto& stu : students) {
        double grade = course->_students.at(stu.first).second;
        fout << stu.second.first << "," << stu.first << "," << grade << "," << Student::grade2GPA(grade) << std::endl;
    }

    fout.close();
    std::cout << "Successfully saved course " << course->_name << "'s students info to " << course->_name
              << ".csv" << std::endl;
    return true;
}
