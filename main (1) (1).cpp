#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
// Course class
class Course {
public:
  std::string number;
  std::string title;
  std::vector<std::string> prerequisites;
  // Constructor
  Course(const std::string& num, const std::string& t, const std::vector<std::string>& pre) :
    number(num), title(t), prerequisites(pre) {}
};
// Function to load courses from a file
std::vector<Course> loadCourses(const std::string& filename) {
  std::vector<Course> courses;
  std::ifstream file(filename);
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      // Parse the line (assuming format: "CS101,Introduction to Computer Science,CS100")
      size_t comma1 = line.find(',');
      size_t comma2 = line.find(',', comma1 + 1);
      std::string courseNumber = line.substr(0, comma1);
      std::string courseTitle = line.substr(comma1 + 1, comma2 - comma1 - 1);
      std::string prereqs = line.substr(comma2 + 1);
      // Split the prerequisites string into a vector
      std::vector<std::string> preList;
      if (!prereqs.empty()) { // If there are prerequisites
        size_t pos = 0;
        while ((pos = prereqs.find(",")) != std::string::npos) {
          preList.push_back(prereqs.substr(0, pos));
          prereqs.erase(0, pos + 1);
        }
        preList.push_back(prereqs); // Add the last prerequisite
      }
      courses.push_back(Course(courseNumber, courseTitle, preList));
    }
    file.close();
  } else {
    std::cerr << "Error: Unable to open file " << filename << std::endl;
  }
  return courses;
}
// Function to print the course list in alphanumeric order
void printCourseList(const std::vector<Course>& courses) {
  std::vector<Course> sortedCourses = courses;
  std::sort(sortedCourses.begin(), sortedCourses.end(),
    [](const Course& a, const Course& b) { 
      return a.number < b.number; 
    });
  std::cout << "\nCourse List:\n";
  for (const Course& course : sortedCourses) {
    std::cout << course.number << " - " << course.title << std::endl;
  }
}
// Function to print course information
void printCourseInfo(const std::vector<Course>& courses) {
  std::string courseNumber;
  std::cout << "\nEnter course number: ";
  std::cin >> courseNumber;
  bool found = false;
  for (const Course& course : courses) {
    if (course.number == courseNumber) {
      std::cout << "\nCourse Title: " << course.title << std::endl;
      if (!course.prerequisites.empty()) {
        std::cout << "Prerequisites:\n";
        for (const std::string& pre : course.prerequisites) {
          std::cout << pre << std::endl;
        }
      }
      found = true;
      break;
    }
  }
  if (!found) {
    std::cerr << "Error: Course not found.\n";
  }
}
// Main function
int main() {
  std::vector<Course> courseData;
  int choice;
  do {
    std::cout << "\nAdvising Assistance Menu:\n";
    std::cout << "1. Load Course Data\n";
    std::cout << "2. Print Course List\n";
    std::cout << "3. Print Course Information\n";
    std::cout << "9. Exit\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    switch (choice) {
      case 1: {
        std::string filename;
        std::cout << "Enter filename: ";
        std::cin >> filename;
        courseData = loadCourses(filename);
        break;
      }
      case 2:
        printCourseList(courseData);
        break;
      case 3:
        printCourseInfo(courseData);
        break;
      case 9:
        std::cout << "Exiting program.\n";
        break;
      default:
        std::cerr << "Invalid choice. Please try again.\n";
    }
  } while (choice != 9);
  return 0;
}
