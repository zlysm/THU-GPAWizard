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
    for (auto& course : _courses) {
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
