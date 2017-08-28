//
//
//

#include "logiath/logiath.hpp"

#include "util.hpp"

using namespace logiath;

int main(int, char *[]) {
  SeverityFilter<severity::ALERT> alert;
  Logiath<example::FileOutput> logger;

  logger.log(ALERT, "message 1");

  return 0;
}
