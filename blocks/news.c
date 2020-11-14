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
#define BUFLENGTH           5

void
newsu(char *str, int sigval, BlockData *blockdata)
{
  char buf[BUFLENGTH];
  buf[getcmdout(NEWSBOATRELOAD, buf, BUFLENGTH) - 1] = '\0';
  char *unread = strtok(buf, " ");

  char *cursor = unread;
  while (*cursor) {
    if (!isdigit(*cursor))
      return;
    cursor++;
  }

  if (strcmp(unread, "0"))
    snprintf(str, CMDLENGTH, BLOCK_SUCCESS(ICON(ICON0), "%s"), unread);
  else
    printempty(str);
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
