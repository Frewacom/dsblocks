#include <time.h>

#include "../util.h"
#include "time.h"

void
timeu(char *str, int sigval)
{
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  strftime(str, CMDLENGTH, LABEL(ICON_EMPTY "%A, %d %b (w.%W) %T"), &tm);
}
