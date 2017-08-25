//
//
//

#include "gtest/gtest.h"
// using testing::Test

#include <cstdlib>
// using std::exit

#include "logiath/logiath.hpp"

namespace {

class test_logiath : public testing::Test {
 public:
  test_logiath() {}
};

TEST_F(test_logiath, foo) {
  EXPECT_TRUE(true);
}

}  // namespace anonymous end
