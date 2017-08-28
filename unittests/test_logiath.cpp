//
//
//

#include "gtest/gtest.h"
// using testing::Test

#include "logiath/logiath.hpp"

#include <iostream>
// using std::cerr

#include <string>
// using std::string

using namespace logiath;

namespace {

struct CerrOutput {
  static void open() {}
  static void close() {}

  template <typename T>
  static void print(const T &v) {
    std::cerr << v;
  }
};

class test_logiath : public testing::Test {
 public:
  test_logiath() {}
};

TEST_F(test_logiath, no_output) {
  SeverityFilter<severity::ALERT> alert;

  Logiath<NoOutput> logger;
  logger.log(ALERT, "test");

  EXPECT_TRUE(true);
}

TEST_F(test_logiath, err_output) {
  SeverityFilter<severity::ALERT> alert;
  std::string txt{"more test"};

  Logiath<CerrOutput, decltype(alert), NoPrefix> logger;
  logger.log(ALERT, "test", " ", txt);

  logger.set_severity(WARN);
  logger.log(WARN, "this is a warning");
  logger.log(ALERT, "this is an alert");

  EXPECT_TRUE(true);
}

}  // namespace anonymous end
