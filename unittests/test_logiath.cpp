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

TEST_F(test_logiath, alert_filter_debug_message) {
  Logiath<example::StringStreamOutput, SeverityFilter<severity::ALERT> > logger;

  std::string msg{"message 1"};
  logger.log(DEBUG, msg);
  msg += "\n";

  auto cmp = msg.compare(logger.to_string());

  EXPECT_TRUE(!cmp);
}

TEST_F(test_logiath, alert_filter_emerg_message) {
  Logiath<example::StringStreamOutput, SeverityFilter<severity::ALERT> > logger;

  std::string empty{""};
  logger.log(EMERG, "message 1");

  auto cmp = empty.compare(logger.to_string());

  EXPECT_TRUE(!cmp);
}

TEST_F(test_logiath, alert_filter_varying_severity_message) {
  Logiath<example::StringStreamOutput, SeverityFilter<severity::ALERT> > logger;

  std::string msg{""}, total_msg{""};

  msg = "message 1";
  logger.log(EMERG, msg);

  msg = "message 2";
  logger.log(ALERT, msg);
  total_msg += msg + "\n";

  logger.set_severity(CRIT);

  msg = "message 3";
  logger.log(ALERT, msg);

  auto cmp = total_msg.compare(logger.to_string());

  EXPECT_TRUE(!cmp);
}

}  // namespace anonymous end
