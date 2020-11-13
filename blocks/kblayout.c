#include <X11/XKBlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../util.h"
#include "kblayout.h"

#define ICON0                             ""
#define LAYOUT_INDEX_OFFSET               3
#define LAYOUT_INDEX_RANGE                2

void
kblayoutu(char *str, int sigval, XrmDatabase db)
{
  Display* dpy;
  char* displayName = "";
  dpy = XOpenDisplay(displayName);

  XkbDescRec* desc = XkbAllocKeyboard();
  XkbGetNames(dpy, XkbSymbolsNameMask, desc);
  Atom symName = desc -> names -> symbols;
  char* data = XGetAtomName(dpy, symName);

  XCloseDisplay(dpy);

  char layout[LAYOUT_INDEX_RANGE + 1];
  if (strlen(data) > LAYOUT_INDEX_OFFSET + LAYOUT_INDEX_RANGE) {
    strncpy(layout, data+LAYOUT_INDEX_OFFSET, LAYOUT_INDEX_RANGE);

    char *upper = layout;
    while (*upper) {
      *upper = toupper(*upper);
      upper++;
    }

    snprintf(str, CMDLENGTH, BLOCK_NORM(ICON(ICON0), "%s"), layout);
  }
}

void
kblayoutc(int sigval)
{
  system("switch-kb-layout");
}
