#include <stdio.h>

#include "../util.h"
#include "volume.h"

#define ICON0                           ""
#define ICON1                           ""

#define BUFLENGTH                       10

#define PAMIXER                         (char *[]){ "/usr/bin/pamixer", "--get-mute", "--get-volume", NULL }

#define PULSEMIXER                      (char *[]){ "/usr/bin/pulsemixer", NULL }
#define SETDEFAULTVOL                   (char *[]){ "/usr/bin/pamixer", "--set-volume", "50", NULL }
#define INCREASEVOL                     (char *[]){ "/usr/bin/pamixer", "--increase", "3", NULL }
#define DECREASEVOL                     (char *[]){ "/usr/bin/pamixer", "--decrease", "3", NULL }
#define TOGGLEMUTE                      (char *[]){ "/usr/bin/pamixer", "--toggle-mute", NULL }

void
volumeu(char *str, int sigval, XrmDatabase db)
{
  char buf[BUFLENGTH];

  buf[getcmdout(PAMIXER, buf, BUFLENGTH) - 1] = '\0';
  if (buf[0] == 'f') /* output was `false <volume>' */
    snprintf(str, CMDLENGTH, BLOCK_NORM(ICON(ICON0), "%s%%"), buf + 6);
  else /* output was `true <volume>' */
    snprintf(str, CMDLENGTH, BLOCK_CRITICAL(ICON(ICON1), "%s%%"), buf + 5);
}

void
volumec(int button)
{
  csigself(1,1);
  switch(button) {
    case 1:
      cspawn(TOGGLEMUTE);
      break;
    case 2:
      cspawn(SETDEFAULTVOL);
      break;
    case 3:
      /* cspawn(PULSEMIXER); */
      break;
    case 4:
      cspawn(DECREASEVOL);
      break;
    case 5:
      cspawn(INCREASEVOL);
      break;
  }
}
