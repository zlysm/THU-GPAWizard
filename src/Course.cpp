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
    _students[studentID] = {studentName, 0};
}

void Course::setGrade() {
    if (_students.empty()) {
        std::cout << "No student in " << _name << " course." << std::endl
                  << std::endl;
        return;
    }

    std::cout << "set grade for " << _name << " (course number: " << _number << "): " << std::endl;
    for (auto &_student : _students) {
        std::cout << "Please input the grade of " << _student.first << ": " << std::endl;
        double grade;
        std::cin >> grade;
        _student.second.second = grade;  // _students.secone = <name, grade>
    }

    std::cout << "Grades have been set." << std::endl
              << std::endl;
}

bool Course::setGrade(int studentID) {
    if (_students.find(studentID) == _students.end()) {
        std::cout << "No student with id " << studentID << " in " << _name << " course." << std::endl;
        return false;
    }

    std::cout << "Please input the grade of " << _students.at(studentID).first
              << " for " << _name << ": " << std::endl;

    double grade;
    std::cin >> grade;
    _students.at(studentID).second = grade;
    std::cout << "Grade has been set." << std::endl
              << std::endl;
    return true;
}

void Course::showStudentsRankList() const {
    if (_students.empty()) {
        std::cout << "No student in " << _name << " course." << std::endl;
        return;
    }

    std::vector<StudentInfo> students;  // <name, grade>
    students.reserve(_students.size());
    for (const auto &_student : _students)
        students.emplace_back(_student.second.first, _student.second.second);

    std::sort(students.begin(), students.end(),
              [](const StudentInfo &a, const StudentInfo &b) {
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
