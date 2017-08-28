//
//
//

#include "logiath/logiath.hpp"

using namespace logiath;

struct NoOutputDerived : NoOutput {};

int main(int, char *[]) {
  SeverityFilter<severity::ALERT> alert;
  Logiath<NoOutputDerived> logger;

  logger.log(ALERT, "message 1");

  return 0;
}
