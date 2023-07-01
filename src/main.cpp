#include <fstream>

#include "GradeManager.hpp"

void loadStudents(std::vector<Student*>& students, const std::string& filename);
void loadCourses(std::vector<Course*>& courses, const std::string& filename);

int Student::studentCount = 0;
int Course::courseCount = 0;

int main() {
    std::vector<Student*> students;
    std::vector<Course*> courses;

    loadStudents(students, "shared/students.txt");
    loadCourses(courses, "shared/courses.txt");

    GradeManager manager(students, courses);

    std::cout << "-------------Welcome to GPAWizard!-------------" << std::endl;
    std::cout << "Stages:" << std::endl
              << "1. Student select courses" << std::endl
              << "2. Teacher set grades and push to Academic Affairs" << std::endl
              << "3. Grade reconsideration" << std::endl
              << "4. Show final course report" << std::endl;

    // select courses
    std::cout << std::endl
              << "--------Stage 1: Student select courses--------" << std::endl
              << std::endl;
    std::cout << "Do you want to see all " << Course::getCourseCount() << " courses? (y/n)" << std::endl;
    char choice;
    std::cin >> choice;
    if (choice == 'y' || choice == 'Y')
        for (auto& course : courses)
            std::cout << *course;
    manager.studentSelectCourse();

    // set grades
    std::cout
        << "----------Stage 2: Teacher set grades----------" << std::endl
        << std::endl;
    manager.teacherSetGrade();
    manager.pushGrade();

    std::cout << "All " << Course::getCourseCount()
              << " courses' grades have been pushed to Academic Affairs." << std::endl;
    std::cout << "Do you want to see all courses' students rank? (y/n)" << std::endl;
    std::cin >> choice;
    if (choice == 'y' || choice == 'Y')
        for (auto& course : courses)
            course->showStudentsRankList();

    // grade reconsideration
    std::cout << std::endl
              << "---------Stage 3: Grade reconsideration--------" << std::endl
              << std::endl;
    std::cout << "Please input the student's id you want to query(0 to finish): " << std::endl;
    auto findStudent([&](int id) {
        for (auto& student : students)
            if (student->getID() == id)
                return student;
        return (Student*)nullptr;
    });

    int queryID;
    while (std::cin >> queryID && queryID != 0) {
        auto student = findStudent(queryID);
        if (student == nullptr) {
            std::cout << "Student not found." << std::endl;
            std::cout << "Please input the student's id you want to query(0 to finish): " << std::endl;
            continue;
        }

        student->showCourseReport();
        std::cout << "Please input the course number you want to reconsider(0 to finish): " << std::endl;
        int courseNumber;
        auto findCourse([&](int number) {
            for (auto& course : courses)
                if (course->getCourseInfo().number == number)
                    return course;
            return (Course*)nullptr;
        });

        while (std::cin >> courseNumber && courseNumber != 0) {  // teacher reconsider a course
            auto course = findCourse(courseNumber);
            if (course == nullptr) {
                std::cout << "Course not found." << std::endl;
                std::cout << "Please input the course number you want to reconsider(0 to finish): " << std::endl;
                continue;
            }

            course->setGrade(student->getID());
            manager.pushGrade(courseNumber);
            std::cout << "Successfully pushed grade to Academic Affairs." << std::endl;
            std::cout << "Please input the course number you want to reconsider(0 to finish): " << std::endl;
        }

        std::cout << "Student " << student->getName() << "'s new course report: " << std::endl;
        student->showCourseReport();

        std::cout << "Please input the student's id you want to query(0 to finish): " << std::endl;
    }

    // show final course report
    std::cout << std::endl
              << "-------Stage 4: Show final course report-------" << std::endl
              << std::endl;
    for (const auto& student : students)
        student->showCourseReport();

    return 0;
}

void loadStudents(std::vector<Student*>& students, const std::string& filename) {
    // first line is the number of undergraduate students and graduate students
    // rest of the lines are students info, the first part is undergraduate student
    // lines: name id gender (supervisor) year
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Error opening file " << filename << std::endl;
        exit(1);
    }

    int undergradCount, gradCount;
    fin >> undergradCount >> gradCount;
    for (int i = 0; i < undergradCount; ++i) {
        std::string name;
        int id, gender, year;
        fin >> name >> id >> gender >> year;
        students.push_back(new Undergraduate(name, id, gender, year));
    }

    for (int i = 0; i < gradCount; ++i) {
        std::string name, supervisor;
        int id, gender, year;
        fin >> name >> id >> gender >> supervisor >> year;
        students.push_back(new Graduate(name, id, gender, supervisor, year));
    }
    fin.close();
    std::cout << "Successfully loaded " << undergradCount << " undergraduate students and "
              << gradCount << " graduate students!" << std::endl;
}

void loadCourses(std::vector<Course*>& courses, const std::string& filename) {
    // first line is the number of courses
    // rest of the lines are courses info
    // lines: name id credit
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Error opening file " << filename << std::endl;
        exit(1);
    }

    int courseCount;
    fin >> courseCount;
    for (int i = 0; i < courseCount; ++i) {
        std::string name;
        int id, credit;
        fin >> name >> id >> credit;
        courses.push_back(new Course(name, id, credit));
    }
    fin.close();
    std::cout << "Successfully loaded " << courseCount << " courses!" << std::endl;
}
