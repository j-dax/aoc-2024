#pragma once

#include <iostream>
#include <iterator>
#include <vector>

namespace aoc {
template <typename T>
concept Printable = requires(std::ostream &os, const T &t) {
  { os << t } -> std::same_as<std::ostream &>;
};

template <typename C>
concept Container = requires(C c) {
  { c.begin() } -> std::input_or_output_iterator;
  { c.end() } -> std::sentinel_for<decltype(c.begin())>;
  { c.begin() } -> std::same_as<decltype(c.end())>;
};

template <typename T>
concept PrintableContainer = Container<T> && requires(T c) {
  requires Printable<
      typename std::iterator_traits<decltype(c.begin())>::value_type>;
};

template <PrintableContainer C>
inline std::ostream &operator<<(std::ostream &os, C v) {
  os << "[ ";
  for (auto vi : v) {
    os << vi << " ";
  }
  os << "]";
  return os;
}

template <Printable P>
inline std::ostream &operator<<(std::ostream &os, std::pair<P, P> p) {
  return os << "(" << p.first << "," << p.second << ")";
}
} // namespace aoc
