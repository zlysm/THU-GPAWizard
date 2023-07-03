#include "Student.hpp"

// Person

Person::Person(std::string name, int id, int gender)
    : _name(std::move(name)), _id(id), _gender(gender) {}

int Person::getID() const { return _id; }

const std::string& Person::getName() const { return _name; }

std::string Person::getGender() const {
    return _gender == 1 ? "Male" : "Female";
}

// Date

Date::Date(int year, int month, int day)
    : _year(year), _month(month), _day(day) {}

std::string Date::getBirth() const {
    return std::to_string(_month) + "/" + std::to_string(_day) + "/" + std::to_string(_year);
}

// Student

Student::Student(std::string name, int id, int gender)
    : Person(std::move(name), id, gender) {
    ++studentCount;
    _gpa = 0;
}

Student::~Student() { --studentCount; }

void Student::selectCourse(const CourseInfo& course) {
    _courses.push_back(course);
    _courseGrades[course.number] = 0;
}

void Student::calculateGPA() {
    double sum = 0;
    int totalCredits = 0;
    for (const auto& course : _courses) {
        sum += grade2GPA(_courseGrades.at(course.number)) * course.credits;
        totalCredits += course.credits;
    }
    _gpa = (sum == 0) ? 0 : (sum / totalCredits);  // avoid dividing by zero
}

void Student::showCourseReport() {
    std::cout << std::left;
    std::cout << "-------------Student Course Report-------------" << std::endl;
    std::cout << std::setw(15) << "Student: " << std::setw(10) << _name << _id << std::endl;
    std::cout << std::setw(15) << "Course Name" << std::setw(15) << "Course Number"
              << std::setw(10) << "Credits"
              << "GPA" << std::endl;

    for (const auto& course : _courses)
        std::cout << std::setw(15) << course.name << std::setw(15) << course.number
                  << std::setw(10) << course.credits << std::setprecision(1) << std::fixed
                  << grade2GPA(_courseGrades.at(course.number)) << std::endl;

    std::cout << "Total GPA: " << std::setprecision(2) << _gpa << std::endl;
    std::cout << "-----------------------------------------------" << std::endl
              << std::endl;
}

double Student::getGPA() const { return _gpa; }

int Student::getStudentCount() { return studentCount; }

bool Student::operator<(const Student& stu) const { return _gpa < stu._gpa; }

inline double Student::grade2GPA(double grade) {
    if (grade >= 90)
        return 4.0;
    else if (grade >= 85)
        return 3.6;
    else if (grade >= 80)
        return 3.3;
    else if (grade >= 77)
        return 3.0;
    else if (grade >= 73)
        return 2.6;
    else if (grade >= 70)
        return 2.3;
    else if (grade >= 67)
        return 2.0;
    else if (grade >= 63)
        return 1.6;
    else if (grade >= 60)
        return 1.3;
    else
        return 0;
}

// Undergraduate

Undergraduate::Undergraduate(const std::string& name, int id, int gender, int startYear = 2000)
    : Student(name, id, gender), _startYear(startYear) {}

int Undergraduate::getStartYear() const { return _startYear; }

void Undergraduate::showInfo() const {
    std::cout << "-------Undergraduate Student information-------" << std::endl;
    std::cout << std::left;
    std::cout << std::setw(30) << "          Name: " << _name << std::endl;
    std::cout << std::setw(30) << "          ID: " << _id << std::endl;
    std::cout << std::setw(30) << "          Gender: " << getGender() << std::endl;
    std::cout << std::setw(30) << "          BirthDate: " << getBirth() << std::endl;
    std::cout << std::setw(30) << "          Year: " << _startYear << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
}

// Graduate

Graduate::Graduate(const std::string& name, int id, int gender, std::string supervisor)
    : Student(name, id, gender), _supervisor(std::move(supervisor)) {}

const std::string& Graduate::getSupervisor() const { return _supervisor; }

void Graduate::showInfo() const {
    std::cout << "----------Graduate Student information---------" << std::endl;
    std::cout << std::left;
    std::cout << std::setw(30) << "          Name: " << _name << std::endl;
    std::cout << std::setw(30) << "          ID: " << _id << std::endl;
    std::cout << std::setw(30) << "          Gender: " << getGender() << std::endl;
    std::cout << std::setw(30) << "          BirthDate: " << getBirth() << std::endl;
    std::cout << std::setw(30) << "          SUPERVISOR: " << _supervisor << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
}
