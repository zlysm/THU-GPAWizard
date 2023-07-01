#ifndef COURSE_HPP
#define COURSE_HPP

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

typedef struct {
    std::string name;
    int number, credits;
} CourseInfo;

using StudentInfo = std::pair<std::string, double>;

class Course {
   public:
    Course(std::string name, int number, int credits);

    ~Course();

    CourseInfo getCourseInfo() const;

    void updateStudentList(int studentID, const std::string& studentName);

    void setGrade();  // set grade for all students

    bool setGrade(int studentID);  // set grade for a specific student, return false if student not found

    void showStudentsRankList() const;

    static int getCourseCount();

    friend std::ostream& operator<<(std::ostream& os, const Course& course);

   private:
    std::string _name;
    int _number;
    int _credits;
    static int courseCount;

    std::unordered_map<int, StudentInfo> _students;  // <id, <name, grade>>

    friend class GradeManager;
};

#endif  // COURSE_HPP
