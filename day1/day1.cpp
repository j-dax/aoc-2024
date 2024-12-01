#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace aoc {
typedef std::pair<std::vector<int>, std::vector<int>> zip;

zip read_file(const std::string &filename) {
  std::ifstream file(filename);

  zip value;
  int first, second;
  for (std::string line; std::getline(file, line);) {
    std::stringstream ss(line);
    ss >> first >> second;
    value.first.push_back(first);
    value.second.push_back(second);
  }

  return value;
}

// Day 1 Part 1: Calculate distances
void d1p1(const std::string &filename) {
  auto input = read_file(filename);
  // Calculate the distance between the smallest values in each list
  // Sum the result
  std::sort(input.first.begin(), input.first.end());
  std::sort(input.second.begin(), input.second.end());
  int distance = 0;
  for (int i = 0; i < input.first.size(); i++) {
    distance += std::abs(input.first[i] - input.second[i]);
  }
  std::cout << "Total: " << distance << std::endl;
}

// Day 1 Part 2: Calculate similarity scores
void d1p2(const std::string &filename) {
  auto input = read_file(filename);
  // Generate a similarity score using a location from the first list and the
  // count of that location from the second list
  // Sum the result
  std::cout << "seg" << std::endl;
  std::unordered_map<int, int> counts;
  for (int val : input.second) {
    counts[val]++;
  }
  std::cout << "seg" << std::endl;
  int64_t sum = 0;
  for (int location : input.first) {
    sum += location * counts[location];
  }
  std::cout << "Total: " << sum << std::endl;
}
}; // namespace aoc
