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
    Student(std::string name, int id, int gender);

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
    Undergraduate(const std::string &name, int id, int gender, int startYear);

    int getStartYear() const;

    void showInfo() const override;

   private:
    int _startYear;
};

class Graduate : public Student {
   public:
    Graduate(const std::string &name, int id, int gender, std::string supervisor);

    const std::string &getSupervisor() const;

    void showInfo() const override;

   private:
    std::string _supervisor;
};

#endif  // STUDENT_HPP
