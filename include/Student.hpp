#ifndef STUDENT_HPP
#define STUDENT_HPP

#include "Course.hpp"

class Student {
   public:
    Student(std::string name, int id, int gender);

    ~Student();

    void selectCourse(const CourseInfo &course);

    virtual void showInfo() const = 0;

    void showCourseReport();

    // get functions
    double getGPA() const;
    int getID() const;
    const std::string &getName() const;
    static int getStudentCount();

    bool operator<(const Student &stu) const;

   protected:
    static int studentCount;
    std::string _name;
    int _id;
    int _gender;  // 1 for male, 2 for female

    std::vector<CourseInfo> _courses;
    std::unordered_map<int, double> _courseGrades;
    double _gpa;

    void calculateGPA();

    friend class GradeManager;

   private:
    static double grade2GPA(double);
};

class Undergraduate : public Student {
   public:
    Undergraduate(const std::string &name, int id, int gender, int year);

    int getYear() const;

    void showInfo() const override;

   private:
    int _year;
};

class Graduate : public Student {
   public:
    Graduate(const std::string &name, int id, int gender, std::string supervisor, int year);

    const std::string &getSupervisor() const;

    void showInfo() const override;

   private:
    std::string _supervisor;
    int _year;
};

#endif  // STUDENT_HPP
