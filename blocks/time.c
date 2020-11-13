#include <time.h>

#include "../util.h"
#include "time.h"

/* #define SHOWCALENDAR */

void
timeu(char *str, int sigval, BlockData *blockdata)
{
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  strftime(str, CMDLENGTH, BLOCK_NORM(NO_ICON, "%A, %d %b (w.%W) %T"), &tm);
}

void
timec(int button)
{
  /* TERMCMD(SHOWCALENDAR); */
}
