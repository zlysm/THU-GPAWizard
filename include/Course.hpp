#ifndef COURSE_HPP
#define COURSE_HPP

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

struct CourseInfo {
    std::string name;
    int number, credits;

    CourseInfo(std::string name, int number, int credits)
        : name(std::move(name)), number(number), credits(credits) {}
};

class Course {
   public:
    Course(std::string name, int number, int credits);

    ~Course();

    CourseInfo getCourseInfo() const;

    void updateStudentList(int studentID, const std::string& studentName);

    void setGrade();

    void setGrade(int studentID);

    void showStudentsRankList() const;

    static int getCourseCount();

    friend std::ostream& operator<<(std::ostream& os, const Course& course);

   private:
    std::string _name;
    int _number;
    int _credits;
    static int courseCount;

    std::vector<std::pair<int, std::string>> _students;  // <id, name>
    std::unordered_map<int, double> _stuGrades;          // <id, grade>

    friend class GradeManager;
};

#endif  // COURSE_HPP
