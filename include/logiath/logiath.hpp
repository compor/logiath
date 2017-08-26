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
void print_impl(const T &v, Ts... args) {
  std::cout << v;
  print_impl(args...);
}

}  // namespace detail end

enum class severity : unsigned int {
  NONE = 0,
  EMERG,
  ALERT,
  CRIT,
  ERR,
  WARN,
  NOTICE,
  INFO,
  DEBUG
};

template <severity S>
struct SeverityFilter {
  static severity getSeverity() { return value; }
  static bool isMoreSevere(severity s) { return value > s; }

  template <severity U>
  static bool isMoreSevere(SeverityFilter<U> other) {
    return S >= U;
  }

 protected:
  const static severity value;
};

template <severity S>
const severity SeverityFilter<S>::value = S;

using DebugSeverityFilter = SeverityFilter<severity::DEBUG>;
using LowestSeverityFilter = DebugSeverityFilter;

using EmergSeverityFilter = SeverityFilter<severity::EMERG>;
using HighestSeverityFilter = DebugSeverityFilter;

using NoSeverityFilter = SeverityFilter<severity::NONE>;

struct NoPrefix {
  static std::string getPrefix() { return std::string{""}; }
};

template <typename Output, typename SeverityFilter, typename Prefix>
struct Logiath : SeverityFilter, Prefix {
  template <typename... Ts>
  void log(severity s, Ts... args) {
    if (!SeverityFilter::isMoreSevere(s)) return;

    std::cout << Prefix::getPrefix();

    detail::print_impl(args...);

    return;
  }
};

}  // namespace logiath end

#endif  // header
