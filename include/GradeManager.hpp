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

    void saveStudents(SortType type = SortType::NONE);  // save all students

    bool saveStudents(int studentID, SortType type = SortType::NONE);  // save a student's courses

    bool saveCourses(int courseID, SortType type = SortType::NONE);  // save a course's students

   private:
    std::vector<Student*> _students;
    std::vector<Course*> _courses;
};

#endif  // GRADE_MANAGER_HPP
