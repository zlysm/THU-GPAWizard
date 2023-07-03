#include "IOUtils.hpp"

namespace IO {
void loadStudents(std::vector<Student*>& students, const std::string& filename) {
    // first line is the number of undergraduate students and graduate students
    // rest of the lines are students info, the first part is undergraduate student
    // lines: name id gender (supervisor) year
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Error opening file " << filename << std::endl;
        exit(1);
    }

    int undergradCount, gradCount;
    fin >> undergradCount >> gradCount;
    for (int i = 0; i < undergradCount; ++i) {
        std::string name;
        int id, gender, year;
        fin >> name >> id >> gender >> year;
        students.push_back(new Undergraduate(name, id, gender, year));
    }

    for (int i = 0; i < gradCount; ++i) {
        std::string name, supervisor;
        int id, gender;
        fin >> name >> id >> gender >> supervisor;
        students.push_back(new Graduate(name, id, gender, supervisor));
    }
    fin.close();
    std::cout << "Successfully loaded " << undergradCount << " undergraduate students and "
              << gradCount << " graduate students." << std::endl;
}

void loadCourses(std::vector<Course*>& courses, const std::string& filename) {
    // first line is the number of courses
    // rest of the lines are courses info
    // lines: name id credit
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Error opening file " << filename << std::endl;
        exit(1);
    }

    int courseCount;
    fin >> courseCount;
    for (int i = 0; i < courseCount; ++i) {
        std::string name;
        int id, credit;
        fin >> name >> id >> credit;
        courses.push_back(new Course(name, id, credit));
    }
    fin.close();
    std::cout << "Successfully loaded " << courseCount << " courses." << std::endl;
}

}  // namespace IO