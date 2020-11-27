#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../util.h"
#include "news.h"

#define ICON0               ""

#define NEWSBOATRELOAD      (char *[]){ "/usr/bin/newsboat", \
                                        "--cache-file=/tmp/newsboatreload", \
                                        "-x", "reload", \
                                        "-x", "print-unread", \
                                        NULL }

/* bash script (newsup) reloads newsboat with cron and echoes unreads to this file */
#define UPDATEDIR           "/tmp/newsupdate"
#define BUFLENGTH           5

void
newsu(char *str, int sigval, BlockData *blockdata)
{
  int unread;
  readint(UPDATEDIR, &unread);
  if (unread > 0) {
    snprintf(str, CMDLENGTH, BLOCK_SUCCESS(ICON(ICON0), "%d"), unread);
  } else {
    printempty(str);
  }
}

void
newsc(int button, BlockData *blockdata)
{
  switch (button) {
    case 1:
      TERMCMD("newsboat");
      break;
    case 2:
      csigself(6,1);
      break;
  }
}
