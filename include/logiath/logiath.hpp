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
struct Severity {
  Severity() = default;
  Severity(const Severity &) = delete;

  std::string operator()() const { return std::string{""}; }

  const static severity value;
};

template <severity S>
const severity Severity<S>::value = S;

#define OP(op, S, K, expr)                                       \
  template <severity S, severity K>                              \
  bool operator op(const Severity<S> &s, const Severity<K> &k) { \
    return expr;                                                 \
  }

OP(==, S, K, S == K)
OP(!=, S, K, S != K)
OP(<, S, K, S < K)
OP(<=, S, K, S <= K)
OP(>, S, K, S > K)
OP(>=, S, K, S >= K)

#undef OP

using DebugSeverity = Severity<severity::DEBUG>;
using LowestSeverity = DebugSeverity;

using EmergSeverity = Severity<severity::EMERG>;
using HighestSeverity = DebugSeverity;

using NoSeverity = Severity<severity::NONE>;

struct NoPrefix {
  NoPrefix() = delete;
  NoPrefix(const NoPrefix &) = delete;

  std::string operator()() const { return std::string{""}; }
};

template <typename Output, typename SeverityFilter, typename Prefix>
struct logiath : SeverityFilter {
  template <severity s, typename... Ts>
  void log(Ts... args) {
    if (s > *this) return;

    print_impl(args...);

    return;
  }
};

}  // namespace logiath end

#endif  // header
