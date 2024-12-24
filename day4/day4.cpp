#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace aoc {
struct StringStateMachine {
  std::string string;
  int state;
  int count;

  StringStateMachine(const std::string &s) : string(s), state(0), count(0) {}

  void next_char(char c) {
    if (c == string[state]) {
      state++;
      if (state == string.size()) {
        state = 0;
        count++;
      }
    } else {
      state = c == string[0] ? 1 : 0;
    }
  }

  void reset() { state = 0; }
};

void d4p1(const std::string &path) {
  // scan horizontal, vertical, diagonal, and reverse
  // to find a static string XMAS
  std::vector<std::string> lines;
  {
    std::ifstream file(path);
    for (std::string line; std::getline(file, line);) {
      lines.push_back(line);
    }
  }
  const std::string XMAS = "XMAS";
  constexpr char CONTROL = '.';
  const int ROWS = lines.size();
  const int COLS = lines[0].size();
  auto bounded_char = [](std::vector<std::string> &lines, size_t r, size_t c) {
    if (r < 0 || r >= lines.size())
      return CONTROL;
    if (c < 0 || c >= lines[r].size())
      return CONTROL;
    return lines[r][c];
  };
  // horizontal + reverse
  StringStateMachine forward(XMAS), backward(XMAS);
  int prev0 = 0, prev1 = 0;
  for (auto line : lines) {
    forward.reset();
    backward.reset();
    for (size_t col = 0; col < line.size(); col++) {
      size_t rcol = line.size() - col - 1;
      forward.next_char(line[col]);
      backward.next_char(line[rcol]);
    }
  }

  // vertical + reverse
  for (size_t col = 0; col < COLS; col++) {
    forward.reset();
    backward.reset();
    for (size_t row = 0; row < ROWS; row++) {
      forward.next_char(lines[row][col]);
      size_t rrow = ROWS - row - 1;
      backward.next_char(lines[rrow][col]);
    }
  }

  for (size_t k = 0; k < ROWS + COLS - 1; k++) {
    // top-left to bottom right, reverse
    int row = k < ROWS ? ROWS - k - 1 : 0;
    int col = k < ROWS ? 0 : k - ROWS + 1;
    // restart the state machine for each section
    forward.reset();
    backward.reset();
    while (row < ROWS && col < COLS) {
      forward.next_char(bounded_char(lines, row++, col++));
    }
    while (row >= 0 && col >= 0) {
      backward.next_char(bounded_char(lines, row--, col--));
    }
    // bottom-left to top-right, reverse
    row = k < COLS ? 0 : k - COLS + 1;
    col = k < COLS ? k : COLS - 1;
    forward.reset();
    backward.reset();
    while (row < ROWS && col >= 0) {
      backward.next_char(bounded_char(lines, row++, col--));
    }
    while (row >= 0 && col < COLS) {
      forward.next_char(bounded_char(lines, row--, col++));
    }
  }

  size_t sum = forward.count + backward.count;
  std::cout << "Total: " << sum << std::endl;
}
void d4p2(const std::string &path) {
  std::vector<std::string> lines;
  {
    std::ifstream file(path);
    for (std::string line; std::getline(file, line);) {
      lines.push_back(line);
    }
  }
  size_t sum = 0;
  for (int line_no = 1; line_no < lines.size() - 1; line_no++) {
    for (int index = 1; index < lines[line_no].size() - 1; index++) {
      // scan for the center A, count the Xs and Ss
      // make sure Xs or Ss are not diagonal
      if (lines[line_no][index] == 'A') {
        int checksum = ('M' << 1) + ('S' << 1);
        checksum -= lines[line_no - 1][index - 1];
        checksum -= lines[line_no - 1][index + 1];
        checksum -= lines[line_no + 1][index - 1];
        checksum -= lines[line_no + 1][index + 1];
        bool is_diagonal =
            lines[line_no - 1][index - 1] == lines[line_no + 1][index + 1];
        if (checksum == 0 && !is_diagonal) {
          sum++;
        }
      }
    }
  }
  std::cout << "Total: " << sum << std::endl;
}
} // namespace aoc
