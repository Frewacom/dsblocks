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

#define TOGGLELAYOUT                      "set-kb-layout toggle"

void
kblayoutu(char *str, int sigval, BlockData *blockdata)
{
  XkbDescRec *desc = XkbGetKeyboard(dpy, XkbSymbolsNameMask, XkbUseCoreKbd);
  Atom symName = desc->names->symbols;
  char *symbols = XGetAtomName(dpy, symName);

  char layout[LAYOUT_INDEX_RANGE + 1];
  if (symbols != NULL && strlen(symbols) > LAYOUT_INDEX_OFFSET + LAYOUT_INDEX_RANGE) {
    strncpy(layout, symbols+LAYOUT_INDEX_OFFSET, LAYOUT_INDEX_RANGE);

    char *upper = layout;
    while (*upper) {
      *upper = toupper(*upper);
      upper++;
    }

    *upper = '\0';

    snprintf(str, CMDLENGTH, BLOCK_NORM(ICON(ICON0), "%s"), layout);
  }

  XFree(symbols);
  XkbFreeKeyboard(desc, XkbSymbolsNameMask, True);
}

void
kblayoutc(int sigval, BlockData *blockdata)
{
  system(TOGGLELAYOUT);
}
