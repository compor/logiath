//
//
//

#ifndef LOGIATH_EXAMPLE_UTIL_HPP
#define LOGIATH_EXAMPLE_UTIL_HPP

#include "logiath/logiath.hpp"

using namespace logiath;

#include <string>
// using std::string

#include <iostream>
// using std::cerr

#include <fstream>
// using std::ofstream
// using std::ios::binary
// using std::ios::trunc
// using std::ios::out

#include <sstream>
// using std::stringstream

#include <utility>
// using std::forward

namespace example {

struct NoOutputDerived : NoOutput {};

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

struct FileOutput {
  void open() {
    os.open("example.log", std::ios::out | std::ios::binary | std::ios::trunc);
  }
  void close() { os.close(); }

  template <typename T>
  void print(T &&v) {
    os << v;
  }

 protected:
  std::ofstream os;
};

}  // namespace example end

#endif  //
