//
//
//

#ifndef LOGIATH_HPP
#define LOGIATH_HPP

#include "logiath/config.hpp"

#include <type_traits>
// using std::enable_if

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

#define LOGIATH_SEVERITY(NAME)                        \
  struct NAME##_t final {                             \
    static constexpr severity value = severity::NAME; \
    static constexpr char const *const name = #NAME;  \
  } NAME;

LOGIATH_SEVERITY(EMERG);
LOGIATH_SEVERITY(ALERT);
LOGIATH_SEVERITY(CRIT);
LOGIATH_SEVERITY(ERR);
LOGIATH_SEVERITY(WARN);
LOGIATH_SEVERITY(NOTICE);
LOGIATH_SEVERITY(INFO);
LOGIATH_SEVERITY(DEBUG);

#undef LOGIATH_SEVERITY

template <severity S>
struct SeverityFilter {
  static constexpr severity value = S;
};

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

struct NoPrefix {
  static constexpr auto get() -> const char * { return ""; }
};

struct NewlineSuffix {
  static constexpr auto get() -> const char * { return "\n"; }
};

struct NoOutput {
  static void open() {}
  static void close() {}

  template <typename T>
  static void print(const T &) {}
};

template <typename Output, typename SeverityFilter = LowestSeverityFilter,
          typename Prefix = NoPrefix, typename Suffix = NewlineSuffix,
          bool = std::is_base_of<Output, NoOutput>::value>
class Logiath : SeverityFilter, Prefix, Suffix, detail::Printer<Output> {
 protected:
  using printer = detail::Printer<Output>;

 public:
  using output_policy = Output;
  using prefix_policy = Prefix;
  using suffix_policy = Suffix;
  using severity_filter_policy = SeverityFilter;

  Logiath() {
    m_severity = severity_filter_policy::value;
    Output::open();
  }

  ~Logiath() { Output::close(); }

  Logiath(const Logiath &) = delete;
  Logiath &operator=(const Logiath &) = delete;

  template <typename S, typename... Ts>
  typename std::enable_if<(S::value >= SeverityFilter::value)>::type log(
      S s, Ts... args) {
    if (S::value < m_severity) return;

    printer::vprint(Prefix::get(), args...);
    printer::vprint(Suffix::get());
  }

  template <typename S, typename... Ts>
  typename std::enable_if<(S::value < SeverityFilter::value)>::type log(
      S s, Ts... args) {}

  severity get_severity() const { return m_severity; }
  void set_severity(severity s) { m_severity = s; }
  template <typename S>
  void set_severity(S s) {
    m_severity = S::value;
  }

 protected:
  severity m_severity;
};

template <typename Output, typename SeverityFilter, typename Prefix,
          typename Suffix>
class Logiath<Output, SeverityFilter, Prefix, Suffix, true> {
 public:
  using output_policy = NoOutput;

  Logiath() = default;
  ~Logiath() = default;

  Logiath(const Logiath &) = delete;
  Logiath &operator=(const Logiath &) = delete;

  template <typename... Ts>
  void log(Ts... args) {}
};

}  // namespace logiath end

#endif  // header
