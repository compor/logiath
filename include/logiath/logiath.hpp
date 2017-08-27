//
//
//

#ifndef LOGIATH_HPP
#define LOGIATH_HPP

#include <string>
// using std::string

#include <iostream>
// using std::cerr

namespace logiath {

enum class severity : unsigned int {
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
  static bool isHigherThan(severity s) { return value > s; }

  template <severity U>
  static bool isHigherThan(const SeverityFilter<U> &other) {
    return S > U;
  }

 protected:
  const static severity value;
};

template <severity S>
const severity SeverityFilter<S>::value = S;

using EmergSeverityFilter = SeverityFilter<severity::EMERG>;
using LowestSeverityFilter = EmergSeverityFilter;
using DebugSeverityFilter = SeverityFilter<severity::DEBUG>;
using HighestSeverityFilter = DebugSeverityFilter;

namespace detail {

template <typename Output>
struct Printer : Output {
  template <typename T>
  static void vprint(const T &v) {
    Output::print(v);
  }

  template <typename T, typename... Ts>
  static void vprint(const T &v, Ts... args) {
    Output::print(v);
    vprint(args...);
  }
};

}  // namespace detail end

struct NoOutput {
  static void open() {}
  static void close() {}

  template <typename T>
  static void print(const T &) {}
};

struct CerrOutput {
  static void open() {}
  static void close() {}

  template <typename T>
  static void print(const T &v) {
    std::cerr << v;
  }
};

template <typename Output, typename SeverityFilter, typename Prefix>
struct Logiath : SeverityFilter, Prefix, detail::Printer<Output> {
  using output_policy = Output;
  using prefix_policy = Prefix;
  using severity_filter_policy = SeverityFilter;

  Logiath() { Output::open(); }
  ~Logiath() { Output::close(); }

  Logiath(const Logiath &) = delete;
  Logiath &operator=(const Logiath &) = delete;

  template <typename... Ts>
  void log(severity s, Ts... args) {
    if (SeverityFilter::isHigherThan(s)) return;

    detail::Printer<Output>::vprint(Prefix::getPrefix(), args...);
  }
};

}  // namespace logiath end

#endif  // header
