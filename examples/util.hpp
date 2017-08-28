//
//
//

#ifndef LOGIATH_EXAMPLE_UTIL_HPP
#define LOGIATH_EXAMPLE_UTIL_HPP

#include <string>
// using std::string

#include <iostream>
// using std::cerr

#include <sstream>
// using std::stringstream

#include <utility>
// using std::forward

namespace example {

struct CerrOutput {
  static void open() {}
  static void close() {}

  template <typename T>
  static void print(T &&v) {
    std::cerr << v;
  }
};

struct StringStreamOutput {
  static void open() {}
  static void close() {}

  template <typename T>
  void print(T &&v) {
    ss << v;
  }

  std::string to_string() const { return ss.str(); }

 protected:
  std::stringstream ss;
};

}  // namespace example end

#endif  //
