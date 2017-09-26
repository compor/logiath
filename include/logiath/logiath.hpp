//
//
//

#ifndef LOGIATH_HPP
#define LOGIATH_HPP

#include "logiath/config.hpp"

#include <utility>
// using std::forward

#include <type_traits>
// using std::enable_if
// using std::is_base_of

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
struct Severity;

#define LOGIATH_SEVERITY(NAME)                        \
  template <>                                         \
  struct Severity<severity::NAME> {                   \
    static constexpr severity value = severity::NAME; \
    static constexpr char const *const name = #NAME;  \
  };                                                  \
                                                      \
  inline Severity<severity::NAME> NAME() { return Severity<severity::NAME>(); }

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
  void vprint(T &&v) {
    Output::print(std::forward<T>(v));
  }

  template <typename T, typename... Ts>
  void vprint(T &&v, Ts &&... args) {
    Output::print(std::forward<T>(v));
    vprint(std::forward<Ts>(args)...);
  }
};

template <severity S, severity K>
using is_lt = typename std::enable_if<(S < K)>::type;

template <severity S, severity K>
using is_le = typename std::enable_if<(S <= K)>::type;

template <severity S, severity K>
using is_gt = typename std::enable_if<(S > K)>::type;

template <severity S, severity K>
using is_ge = typename std::enable_if<(S >= K)>::type;

template <severity S, severity K>
using are_eq = typename std::enable_if<(S == K)>::type;

}  // namespace detail end

struct NoPrefix {
  constexpr auto get_prefix() const -> const char * { return ""; }
};

struct NewlineSuffix {
  constexpr auto get_suffix() const -> const char * { return "\n"; }
};

struct NoOutput {
  void open() {}
  void close() {}

  template <typename T>
  void print(T &&) {}
};

template <typename Output, typename SeverityFilter = LowestSeverityFilter,
          typename Prefix = NoPrefix, typename Suffix = NewlineSuffix,
          bool = std::is_base_of<Output, NoOutput>::value>
class Logiath : SeverityFilter, Prefix, Suffix, public detail::Printer<Output> {
 protected:
  using printer = detail::Printer<Output>;

 public:
  using output_policy = Output;
  using prefix_policy = Prefix;
  using suffix_policy = Suffix;
  using severity_filter_policy = SeverityFilter;

  Logiath() {
    m_severity = severity_filter_policy::value;
    output_policy::open();
  }

  ~Logiath() { output_policy::close(); }

  Logiath(const Logiath &) = delete;
  Logiath &operator=(const Logiath &) = delete;

  template <typename Sev, typename... Ts>
  detail::is_le<Sev::value, severity_filter_policy::value> log(Sev s,
                                                               Ts &&... args) {
    if (Sev::value > m_severity) return;

    printer::vprint(prefix_policy::get_prefix(), std::forward<Ts>(args)...);
    printer::vprint(suffix_policy::get_suffix());
  }

  template <typename Sev, typename... Ts>
  detail::is_gt<Sev::value, severity_filter_policy::value> log(Sev s,
                                                               Ts &&... args) {}

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
  using output_policy = Output;

  Logiath() = default;
  ~Logiath() = default;

  Logiath(const Logiath &) = delete;
  Logiath &operator=(const Logiath &) = delete;

  template <typename... Ts>
  void log(Ts &&... args) {}
};

}  // namespace logiath end

#endif  // header
