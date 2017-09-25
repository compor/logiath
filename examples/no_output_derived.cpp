//
//
//

#include "util.hpp"

using namespace logiath;

int main(int, char *[]) {
  SeverityFilter<severity::ALERT> alert;
  Logiath<example::NoOutputDerived> logger;
  //Logiath<example::NoOutputDerived, decltype(alert)> logger;

  logger.log(ALERT(), "message 1");

  return 0;
}
