//
//
//

#ifndef LOGIATH_HPP
#define LOGIATH_HPP

#include <string>
// using std::string

#include <iostream>
// using std::ostream
// using std::cout
// using std::endl

namespace logiath {

namespace detail {

void print_impl() { std::cout << std::endl; }

template <typename T, typename... Ts>
void print_impl(T v, Ts... args) {
  std::cout << v;
  print_impl(args...);
}

}  // namespace detail end

enum class severity_t : unsigned int {
  EMERG,
  ALERT,
  CRIT,
  ERR,
  WARN,
  NOTICE,
  INFO,
  DEBUG
};

template <severity_t severity>
struct Severity {
  Severity() = delete;
  Severity(const Severity &) = delete;

  const std::string &operator() const { return std::string{""}; }

  severity_t value = severity;
};

template <typename Output, typename SeverityFilter, typename Prefix>
struct logiath {
  template <typename... Ts>
  void log(Ts... args) {
    print_impl(args...);

    return;
  }
};

}  // namespace logiath end

#endif  // header
