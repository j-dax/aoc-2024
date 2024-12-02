#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace aoc {
struct Report {
  std::vector<int> levels;

  bool is_fault(int a, int b) {
    int c = std::abs(a - b);
    return c < 1 || c > 3;
  };

  bool is_safe(int fault_tolerance) {
    if (fault_tolerance == 0) {
      int num_decreasing = 0;
      int num_increasing = 0;
      int num_faults = 0;

      int prev = levels[0];
      for (size_t index = 1; index < levels.size(); index++) {
        if (is_fault(prev, levels[index]))
          num_faults++;
        if (prev < levels[index])
          num_increasing++;
        if (prev > levels[index])
          num_decreasing++;
        prev = levels[index];
      }

      return num_faults == 0 && (num_decreasing == 0 || num_increasing == 0);
    } else {
      for (size_t index = 0; index < levels.size(); index++) {
        int n = levels[index];
        levels.erase(levels.begin() + index);
        bool subvec_is_safe = is_safe(fault_tolerance - 1);
        levels.insert(levels.begin() + index, n);
        if (subvec_is_safe)
          return true;
      }
      return false;
    }
  }

  static std::vector<Report> read_file(const std::string &path) {
    std::ifstream file(path);
    std::vector<Report> reports;
    for (std::string line; std::getline(file, line);) {
      std::vector<int> report;
      std::stringstream ss(line);
      int n;
      while (ss >> n) {
        report.push_back(n);
      }
      reports.push_back({report});
    }
    return reports;
  }
};

// Day 2, Part 1
void d2p1(const std::string &path) {
  auto reports = Report::read_file(path);
  // How many reports are all gradually (within 1 - 3) increasing or decreasing
  int num_safe = 0;
  for (auto report : reports) {
    if (report.is_safe(0)) {
      num_safe++;
    }
  }
  std::cout << "Safe reports: " << num_safe << std::endl;
}
void d2p2(const std::string &path) {
  auto reports = Report::read_file(path);
  // How many reports are all gradually (within 1 - 3) increasing or decreasing
  // Now, tolerate one bad level
  const int tolerance = 1;
  int num_safe = 0;
  for (auto report : reports) {
    if (report.is_safe(tolerance)) {
      num_safe++;
    }
  }
  std::cout << "Safe reports: " << num_safe << std::endl;
}
}; // namespace aoc
