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
  Severity<severity::ALERT> alert;
  Severity<severity::ERR> err;

  auto cmp1 = (alert < err);
  auto cmp2 = (alert > err);
  auto cmp3 = (alert > severity::alert);

  EXPECT_TRUE(cmp1 && !cmp2);
}

}  // namespace anonymous end
