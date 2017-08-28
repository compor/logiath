//
//
//

#ifndef LOGIATH_HPP
#define LOGIATH_HPP

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
          typename Prefix = NoPrefix, typename Suffix = NewlineSuffix>
class Logiath : SeverityFilter, Prefix, Suffix, detail::Printer<Output> {
 protected:
  using printer = detail::Printer<Output>;

 public:
  using output_policy = Output;
  using prefix_policy = Prefix;
  using suffix_policy = Suffix;
  using severity_filter_policy = SeverityFilter;

  Logiath() { Output::open(); }
  ~Logiath() { Output::close(); }

  Logiath(const Logiath &) = delete;
  Logiath &operator=(const Logiath &) = delete;

  template <typename... Ts>
  void log(severity s, Ts... args) {
    if (SeverityFilter::isHigherThan(s)) return;

    printer::vprint(Prefix::get(), args...);
    printer::vprint(Suffix::get());
  }
};

template <typename SeverityFilter, typename Prefix, typename Suffix>
class Logiath<NoOutput, SeverityFilter, Prefix, Suffix> {
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
