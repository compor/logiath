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

enum class log_severity : unsigned int { INFO, DEBUG };

template <const std::string &prefix>
class logger {
 public:
  template <log_severity severity, typename... Ts>
  void print(Ts... args) {
    switch (severity) {
      case (log_severity::INFO):
        std::cout << "[INFO] ";
        break;
      case (log_severity::DEBUG):
        std::cout << "[DEBUG] ";
        break;
      default:
        std::cout << "[UNKNOWN] ";
        break;
    }

    std::cout << prefix << ": ";

    print_impl(args...);

    return;
  }

 private:
  void print_impl() {
    std::cout << std::endl;
    return;
  }

  template <typename T, typename... Ts>
  void print_impl(T v, Ts... args) {
    std::cout << v;
    print_impl(args...);

    return;
  }
};

extern const std::string log_prefix{"LOGIATH"};

static logger<log_prefix> logiath;

#define LOG_INFO logiath.print<log_severity::INFO>
#define LOG_DEBUG logiath.print<log_severity::DEBUG>

#endif  // header
