//
//
//

#include "gtest/gtest.h"
// using testing::Test

#include <string>
// using std::string

#include "logiath/logiath.hpp"

#include "examples/util.hpp"

using namespace logiath;

namespace {

class test_logiath : public testing::Test {
 public:
  test_logiath() {}
};

TEST_F(test_logiath, alert_filter_alert_message) {
  Logiath<example::StringStreamOutput, SeverityFilter<severity::ALERT> > logger;

  std::string msg{"message 1"};
  logger.log(ALERT, msg);
  msg += "\n";

  auto cmp = msg.compare(logger.to_string());

  EXPECT_TRUE(!cmp);
}

}  // namespace anonymous end
