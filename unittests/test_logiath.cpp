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

TEST_F(test_logiath, severity_comparisons) {
  SeverityFilter<severity::ALERT> alert;
  SeverityFilter<severity::ERR> err;

  auto cmp1 = err.isHigherThan(alert);
  auto cmp2 = alert.isHigherThan(err);
  auto cmp3 = err.isHigherThan(severity::ALERT);

  EXPECT_TRUE(cmp1 && !cmp2 && cmp3);
}

TEST_F(test_logiath, no_output) {
  SeverityFilter<severity::ALERT> alert;

  Logiath<NoOutput> logger;
  logger.log(severity::ALERT, "test");

  EXPECT_TRUE(true);
}

TEST_F(test_logiath, err_output) {
  SeverityFilter<severity::ALERT> alert;
  std::string txt{"more test"};

  Logiath<CerrOutput, decltype(alert), NoPrefix> logger;
  logger.log(severity::ALERT, "test", " ", txt);

  EXPECT_TRUE(true);
}

}  // namespace anonymous end
