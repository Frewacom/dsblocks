#include <stdio.h>
#include <string.h>
#include "../util.h"
#include "news.h"

#define ICON0               ""

#define UNREADPATH          "/tmp/newsupdate"

void
newsu(char *str, int sigval)
{
  int unread;
  if (readint(UNREADPATH, &unread)) {
    snprintf(str, CMDLENGTH, BLOCK_SUCCESS(ICON(ICON0), "%d"), unread);
    return;
  }
}

void
newsc(int button)
{
  TERMCMD("newsboat");
}
