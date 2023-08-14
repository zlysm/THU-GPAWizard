#ifndef STUDENT_HPP
#define STUDENT_HPP

#include "Course.hpp"

class Person {
   public:
    Person(std::string name, int id, int gender);

    int getID() const;

    const std::string &getName() const;

    std::string getGender() const;

   protected:
    std::string _name;
    int _id;
    int _gender;  // 1 for male, 2 for female
};

class Date {
   public:
    explicit Date(int year = 2000, int month = 1, int day = 1);

    std::string getBirth() const;

   protected:
    int _year;
    int _month;
    int _day;
};

class Student : public Person, public Date {
   public:
    Student(std::string name, int id, int gender, int year, int month, int day);

    virtual ~Student();

    void selectCourse(const CourseInfo &course);

    void calculateGPA();

    void showCourseReport();

    double getGPA() const;

    static int getStudentCount();

    virtual void showInfo() const = 0;

    bool operator<(const Student &stu) const;

   protected:
    std::vector<CourseInfo> _courses;
    std::unordered_map<int, double> _courseGrades;
    double _gpa;

    static int studentCount;
    friend class GradeManager;

   private:
    static double grade2GPA(double);
};

class Undergraduate : public Student {
   public:
    Undergraduate(std::string name, int id, int gender, int year, int month, int day, int startYear = 2000);

    int getStartYear() const;

    void showInfo() const override;

   private:
    int _startYear;
};

class Graduate : public Student {
   public:
    Graduate(std::string name, int id, int gender, int year, int month, int day, std::string supervisor);

    const std::string &getSupervisor() const;

    void showInfo() const override;

   private:
    std::string _supervisor;
};

#endif  // STUDENT_HPP
