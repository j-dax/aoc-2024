#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../printable.h"

namespace aoc {
struct Rule {
  std::vector<int> values;

  int middle() { return values[values.size() / 2]; }
};

std::ostream &operator<<(std::ostream &os, Rule r) {
  return os << "Rule{ .values=" << r.values << " }";
}

struct Input {
  std::vector<Rule> rules;
  std::vector<std::pair<int, int>> pairs;

  bool validate_rule(Rule rule) {
    auto end = rule.values.end();
    auto begin = rule.values.begin();
    for (auto [first, second] : pairs) {
      auto first_it = std::find(begin, end, first);
      auto second_it = std::find(begin, end, second);
      if (first_it != end && second_it != end && first_it > second_it) {
        return false;
      }
    }
    return true;
  }

  void fix(Rule &rule) {
    std::unordered_map<int, int> before;
    for (auto [first, second] : pairs) {
      auto f_it = std::find(rule.values.begin(), rule.values.end(), first);
      auto s_it = std::find(rule.values.begin(), rule.values.end(), second);
      if (f_it != rule.values.end() && s_it != rule.values.end())
        before[first]++;
    }
    std::sort(rule.values.begin(), rule.values.end(),
              [&before](int a, int b) { return before[a] < before[b]; });
  }

  static Input read_file(const std::string &path) {
    // Generate an ordered list of keys from the first set of lines
    std::vector<Rule> rules;
    std::vector<std::pair<int, int>> pairs;
    std::ifstream file(path);
    if (!file.is_open()) {
      std::cerr << "Failed to open file" << std::endl;
      exit(1);
    }
    for (std::string line; std::getline(file, line);) {
      if (line.size() == 0)
        break; // this is the line just before the rules appear
      long pipe_index = line.find('|'); // unsafe, skipping npos check
      std::string s = line.substr(0, pipe_index);
      int first = std::stoi(s);
      s = line.substr(pipe_index + 1);
      int second = std::stoi(s);
      pairs.push_back({first, second});
    }
    for (std::string line; std::getline(file, line);) {
      std::vector<int> current_rule;
      long index = 0;
      while (index != line.size()) {
        unsigned long next = std::min(line.find(',', index), line.size());
        std::string s = line.substr(index, next);
        current_rule.push_back(std::stoi(s));
        index = std::min(next + 1, line.size());
      }
      rules.push_back({current_rule});
    }
    return {rules, pairs};
  }
};

/*
 * Generate a valid ordering from a list of rules
 * Then validate each set of rules
 */
void d5p1(const std::string &path) {
  Input inp = Input::read_file(path);
  int sum = 0;
  for (auto rule : inp.rules) {
    if (inp.validate_rule(rule)) {
      sum += rule.middle();
    }
  }
  std::cout << sum << std::endl;
}
// Now fix the bad orderings
void d5p2(const std::string &path) {
  Input inp = Input::read_file(path);
  int sum = 0;
  for (auto rule : inp.rules) {
    if (!inp.validate_rule(rule)) {
      inp.fix(rule);
      sum += rule.middle();
    }
  }
  std::cout << sum << std::endl;
}
} // namespace aoc
