#ifndef GRADE_MANAGER_HPP
#define GRADE_MANAGER_HPP

#include "IOUtils.hpp"
#include "Student.hpp"

class GradeManager {
   public:
    GradeManager(std::vector<Student*>& students, std::vector<Course*>& courses);

    ~GradeManager();

    void studentSelectCourse();

    void teacherSetGrade();

    void pushGrade();  // when teacher set all course's grade, push it to students

    bool pushGrade(int courseNumber);  // modify a course's grade

   private:
    std::vector<Student*> _students;
    std::vector<Course*> _courses;
};

#endif  // GRADE_MANAGER_HPP
