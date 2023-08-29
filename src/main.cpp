#include "GradeManager.hpp"
#include "IOUtils.hpp"

int Student::studentCount = 0;
int Course::courseCount = 0;

int main() {
    std::vector<Student*> students;
    std::vector<Course*> courses;

    IO::loadStudents(students, "shared/students.txt");
    IO::loadCourses(courses, "shared/courses.txt");

    GradeManager manager(students, courses);

    std::cout << "-------------Welcome to GPAWizard!-------------" << std::endl;
    std::cout << "Stages:" << std::endl
              << "1. Student select courses" << std::endl
              << "2. Teacher set grades and push to Academic Affairs" << std::endl
              << "3. Grade query and reconsideration" << std::endl
              << "4. Show final course report" << std::endl
              << "5. Save Students and Courses" << std::endl;

    // select courses
    std::cout << std::endl
              << "--------Stage 1: Student select courses--------" << std::endl
              << std::endl;

    char choice = IO::checkInput<char>(
        "Do you want to see all " + std::to_string(Course::getCourseCount()) + " courses? (y/n)");
    if ('n' != choice && 'N' != choice)
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
    choice = IO::checkInput<char>("Do you want to see all courses' students rank? (y/n)");
    if ('n' != choice && 'N' != choice)
        for (auto& course : courses)
            course->showStudentsRankList();

    // grade reconsideration
    std::cout << std::endl
              << "-------Stage 3: Query and Reconsideration------" << std::endl
              << std::endl;

    auto findStudent([&](int id) {
        for (auto& student : students)
            if (student->getID() == id)
                return student;
        return (Student*)nullptr;
    });

    auto findCourse([&](int number) {
        for (auto& course : courses)
            if (course->getCourseInfo().number == number)
                return course;
        return (Course*)nullptr;
    });

    const std::string queryPrompt = "Please input the student's id you want to query(0 to finish): ";
    const std::string reconsiderPrompt = "Please input the course number you want to reconsider(0 to finish): ";

    for (int queryID = IO::checkInput<int>(queryPrompt); 0 != queryID;
         queryID = IO::checkInput<int>(queryPrompt)) {
        auto student = findStudent(queryID);
        if (!student) {
            std::cout << "Student not found." << std::endl;
            continue;
        }
        student->showCourseReport();

        for (int courseNumber = IO::checkInput<int>(reconsiderPrompt); 0 != courseNumber;
             courseNumber = IO::checkInput<int>(reconsiderPrompt)) {  // get course number, 0 to finish
            auto course = findCourse(courseNumber);
            if (!course) {
                std::cout << "Course not found." << std::endl;
                continue;
            }

            if (course->setGrade(student->getID())) {
                manager.pushGrade(courseNumber);
                std::cout << "Successfully pushed grade to Academic Affairs." << std::endl
                          << std::endl;
            }
        }
        std::cout << "Student " << student->getName() << " reconsideration finished." << std::endl
                  << std::endl;
    }

    // show final course report
    std::cout << std::endl
              << "-------Stage 4: Show final course report-------" << std::endl
              << std::endl;
    for (const auto& student : students)
        student->showCourseReport();

    // save students and courses
    std::cout << std::endl
              << "--------Stage 5: Save Students/Courses---------" << std::endl
              << std::endl;

    const std::string savePrompt =
        "Select the sorting method you want(default is 0): \n"
        "1. Name\n"
        "2. ID\n"
        "3. GPA\n";

    choice = IO::checkInput<char>("Do you want to save all " + std::to_string(Student::getStudentCount()) + " students? (y/n)");
    if ('n' != choice && 'N' != choice) {
        int sortType = IO::checkInput<int>(savePrompt);
        manager.saveStudents(static_cast<IO::SortType>(sortType));  // overload function, save all students
        std::cout << std::endl;
    }

    choice = IO::checkInput<char>("Do you want to save a student's courses info? (y/n)");
    if ('n' != choice && 'N' != choice) {
        const std::string studentPrompt = "Please input the student's id(0 to finish): ";
        for (int studentID = IO::checkInput<int>(studentPrompt); 0 != studentID;
             studentID = IO::checkInput<int>(studentPrompt)) {  // get student id, 0 to finish
            if (!findStudent(studentID)) {
                std::cout << "Student not found." << std::endl;
                continue;
            }
            int sortType = IO::checkInput<int>(savePrompt);
            manager.saveStudents(studentID, static_cast<IO::SortType>(sortType));
            std::cout << std::endl;
        }
    }

    choice = IO::checkInput<char>("Do you want to save a course's students info? (y/n)");
    if ('n' != choice && 'N' != choice) {
        const std::string coursePrompt = "Please input the course number(0 to finish): ";
        for (int courseNumber = IO::checkInput<int>(coursePrompt); 0 != courseNumber;
             courseNumber = IO::checkInput<int>(coursePrompt)) {  // get course number, 0 to finish
            if (!findCourse(courseNumber)) {
                std::cout << "Course not found." << std::endl;
                continue;
            }
            int sortType = IO::checkInput<int>(savePrompt);
            manager.saveCourses(courseNumber, static_cast<IO::SortType>(sortType));
            std::cout << std::endl;
        }
    }

    std::cout << "---------------Thanks for using!---------------" << std::endl;

    return 0;
}
