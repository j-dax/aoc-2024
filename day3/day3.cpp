#include <cassert>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

namespace aoc {
void d3p1(const std::string &path) {
  int64_t sum = 0;
  std::regex mul_regex(R"R(^mul\((\d+),(\d+)\))R");
  std::smatch match;

  std::ifstream file(path);
  for (std::string line; std::getline(file, line);) {
    for (size_t index = 0; index < line.size(); index++) {
      char c = line[index];
      // handle do() and don't()
      if (c == 'm') {
        if (std::regex_search(line.cbegin() + index, line.cend(), match,
                              mul_regex)) {
          long first = std::stol(match[1]);
          long second = std::stol(match[2]);
          sum += first * second;
        }
      }
    }
  }
  std::cout << "Total: " << sum << std::endl;
}
void d3p2(const std::string &path) {
  // Each line is guaranteed to have at least one do and one don't
  std::ifstream file(path);

  bool enabled = true;
  int64_t sum = 0;
  std::regex pattern("do\\(\\)|don't\\(\\)|mul\\((\\d+),(\\d+)\\)");
  for (std::string line; std::getline(file, line);) {
    for (auto it = std::sregex_iterator(line.begin(), line.end(), pattern);
         it != std::sregex_iterator(); it++) {
      std::smatch match = *it;
      std::string substr = match.str();
      if (substr.find("do()") == 0) {
        enabled = true;
      } else if (substr.find("don't()") == 0) {
        enabled = false;
      } else if (enabled) {
        auto first = std::next(match.begin());
        auto second = std::next(first);
        sum += std::stoi(*first) * std::stoi(*second);
      }
    }
  }

  std::cout << "Total: " << sum << std::endl;
  assert(sum > 59215249 && sum < 79967531);
}
}; // namespace aoc
