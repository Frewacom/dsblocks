#include <stdio.h>

#include "../util.h"
#include "cputemp.h"

#define ICON0                           COL_SEL "" COL_NORM
#define ICON1                           COL_TITLE "" COL_NORM

#define WARNCPUTEMP                     70000

#define CPUTEMPFILE                     "/sys/class/thermal/thermal_zone0/temp"

void
cputempu(char *str, int sigval, BlockData *blockdata)
{
  int temp;

  if (!readint(CPUTEMPFILE, &temp)) {
    *str = '\0';
    return;
  }
  if (temp < WARNCPUTEMP)
    snprintf(str, CMDLENGTH, ICON0 "%d°C", (temp + 999) / 1000);
  else
    snprintf(str, CMDLENGTH, ICON1 "%d°C", (temp + 999) / 1000);
}

void
cputempc(int button, BlockData *blockdata)
{
  switch (button) {
    case 1:
      TERMCMD("/usr/bin/htop -s PERCENT_CPU");
      break;
    case 2:
      TERMCMD("/usr/bin/htop");
      break;
    case 3:
      TERMCMD("/usr/bin/htop -s PERCENT_MEM");
      break;
  }
}
