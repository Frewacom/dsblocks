#include <time.h>

#include "../util.h"
#include "time.h"

void
timeu(char *str, int sigval)
{
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  strftime(str, CMDLENGTH, ICON("%T", COL_SUCCESS_BG), &tm);
}
