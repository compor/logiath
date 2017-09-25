//
//
//

#include "example.h"

Logiath<NoOutput> logger;

int main(int, char *[]) {
  logger.log(ALERT(), "main message 1");

  return 0;
}
