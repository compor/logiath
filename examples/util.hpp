//
//
//

#ifndef LOGIATH_EXAMPLE_UTIL_HPP
#define LOGIATH_EXAMPLE_UTIL_HPP

namespace example {

struct CerrOutput {
  static void open() {}
  static void close() {}

  template <typename T>
  static void print(const T &v) {
    std::cerr << v;
  }
};

}  // namespace example end

#endif  //
