#include <stdio.h>
#include <string.h>
#include "../util.h"
#include "news.h"

#define ICON0               ""

#define UNREADPATH          "/tmp/newsupdate"

void
newsu(char *str, int sigval, XrmDatabase db)
{
  int unread;
  if (readint(UNREADPATH, &unread)) {
    snprintf(str, CMDLENGTH, BLOCK_SUCCESS(ICON(ICON0), "%d"), unread);
  }
  else {
    printempty(str);
  }
}

void
newsc(int button)
{
  switch (button){
    case 1:
      TERMCMD("newsboat");
      break;
    case 2:
      TERMCMD("newsup");
      break;
  }
}
