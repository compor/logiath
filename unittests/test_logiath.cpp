//
//
//

#include "gtest/gtest.h"
// using testing::Test

#include <cstdlib>
// using std::exit

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

  auto cmp1 = err.isMoreSevere(alert);
  auto cmp2 = alert.isMoreSevere(err);
  auto cmp3 = err.isMoreSevere(severity::ALERT);

  EXPECT_TRUE(cmp1 && !cmp2 && cmp3);
}

TEST_F(test_logiath, output) {
  SeverityFilter<severity::ALERT> alert;

  Logiath<int, decltype(alert), NoPrefix> logger;
  logger.log(severity::ALERT, "test");

  EXPECT_TRUE(true);
}

}  // namespace anonymous end
