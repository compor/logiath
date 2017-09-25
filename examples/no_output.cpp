//
//
//

#include "logiath/logiath.hpp"

using namespace logiath;

int main(int, char *[]) {
  SeverityFilter<severity::ALERT> alert;
  Logiath<NoOutput> logger;
  //Logiath<NoOutput, decltype(alert)> logger;

  logger.log(ALERT(), "message 1");

  return 0;
}
