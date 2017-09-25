//
//
//

#include "util.hpp"

int main(int, char *[]) {
  SeverityFilter<severity::ALERT> alert;
  Logiath<example::FileOutput> logger;
  //Logiath<example::FileOutput, decltype(alert)> logger;

  logger.log(ALERT(), "message 1");

  return 0;
}
