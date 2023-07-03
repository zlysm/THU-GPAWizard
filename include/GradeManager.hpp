#ifndef GRADE_MANAGER_HPP
#define GRADE_MANAGER_HPP

#include "IOUtils.hpp"

using IO::SortType;

class GradeManager {
   public:
    GradeManager(std::vector<Student*>& students, std::vector<Course*>& courses);

    ~GradeManager();

    void studentSelectCourse();

    void teacherSetGrade();

    void pushGrade();  // when teacher set all course's grade, push it to students

    bool pushGrade(int courseNumber);  // modify a course's grade

    void saveStudents(std::vector<Student*> students, SortType type);  // save all students

    bool saveStudents(std::vector<Student*> students, int studentID, SortType type);  // save a student's courses

    bool saveCourses(std::vector<Course*> courses, int courseID, SortType type);  // save a course's students

   private:
    std::vector<Student*> _students;
    std::vector<Course*> _courses;
};

#endif  // GRADE_MANAGER_HPP
