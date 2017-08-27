//
//
//

#include "gtest/gtest.h"
// using testing::Test

#include "logiath/logiath.hpp"

using namespace logiath;

namespace {

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

  Logiath<NoOutput, decltype(alert), NoPrefix> logger;
  logger.log(severity::ALERT, "test");

  EXPECT_TRUE(true);
}

TEST_F(test_logiath, err_output) {
  SeverityFilter<severity::ALERT> alert;

  Logiath<CerrOutput, decltype(alert), NoPrefix> logger;
  logger.log(severity::ALERT, "test");

  EXPECT_TRUE(true);
}

}  // namespace anonymous end
