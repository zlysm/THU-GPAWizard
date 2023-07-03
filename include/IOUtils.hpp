#ifndef IO_UTILS_HPP
#define IO_UTILS_HPP

#include <fstream>
#include <limits>

#include "Course.hpp"
#include "Student.hpp"

namespace IO {
void loadStudents(std::vector<Student*>& students, const std::string& filename);

void loadCourses(std::vector<Course*>& courses, const std::string& filename);

template <typename T>
T checkInput(const std::string& prompt) {
    T input;
    std::cout << prompt;

    while (!(std::cin >> input)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input, please input again!" << std::endl
                  << prompt;
    }

    return input;
}
}  // namespace IO

#endif  // IO_UTILS_HPP
