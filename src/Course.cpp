#include "Course.hpp"

Course::Course(std::string name, int number, int credits)
    : _name(std::move(name)), _number(number), _credits(credits) {
    ++courseCount;
}

Course::~Course() {
    --courseCount;
}

CourseInfo Course::getCourseInfo() const {
    return {_name, _number, _credits};
}

void Course::updateStudentList(int studentID, const std::string &studentName) {
    _students.emplace_back(studentID, studentName);
    _stuGrades[studentID] = 0;
}

void Course::setGrade() {
    if (_students.empty()) {
        std::cout << "No student in " << _name << " course." << std::endl
                  << std::endl;
        return;
    }

    std::cout << "set grade for " << _name << " (course number: " << _number << "): " << std::endl;
    for (const auto &student : _students) {
        std::cout << "Please input the grade of " << student.second << ": " << std::endl;
        double grade;
        std::cin >> grade;
        _stuGrades[student.first] = grade;
    }

    std::cout << "Grades have been set." << std::endl
              << std::endl;
}

void Course::setGrade(int studentID) {
    for (auto &_student : _students)
        if (_student.first == studentID) {
            std::cout << "Please input the grade of " << _student.second
                      << " for " << _name << ": " << std::endl;
            double grade;
            std::cin >> grade;
            _stuGrades[studentID] = grade;
            std::cout << "Grade has been set." << std::endl
                      << std::endl;
            return;
        }
}

void Course::showStudentsRankList() const {
    if (_students.empty()) {
        std::cout << "No student in " << _name << " course." << std::endl
                  << std::endl;
        return;
    }

    std::vector<std::pair<std::string, double>> students;  // <name, grade>
    students.reserve(_students.size());
    for (const auto &_student : _students)
        students.emplace_back(_student.second, _stuGrades.at(_student.first));

    std::sort(students.begin(), students.end(),
              [](const std::pair<std::string, double> &a, const std::pair<std::string, double> &b) {
                  return a.second > b.second;
              });  // sort by grade

    std::cout << "------------------Rank List------------------" << std::endl;
    std::cout << std::left;
    std::cout << std::setw(30) << "          Course: " << _name << std::endl;
    for (const auto &student : students)
        std::cout << std::setw(30) << "          " + student.first + ": " << student.second << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
}

int Course::getCourseCount() {
    return courseCount;
}

std::ostream &operator<<(std::ostream &os, const Course &course) {
    os << "------------------Course Info------------------" << std::endl;
    os << std::left;
    os << std::setw(30) << "          Name: " << course._name << std::endl;
    os << std::setw(30) << "          Number: " << course._number << std::endl;
    os << std::setw(30) << "          Credits: " << course._credits << std::endl;
    os << "-----------------------------------------------" << std::endl;
    return os;
}
