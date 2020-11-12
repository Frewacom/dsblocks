#include <mpd/client.h>
#include <stdio.h>
#include "../util.h"
#include "music.h"

#define ICON0               ""

void
musicu(char *str, int sigval, XrmDatabase db)
{
  /* struct mpd_connection *conn = mpd_connection_new(NULL, 0, 0); */
  /* struct mpd_song *song = mpd_run_current_song(conn); */
  /* const char *title = mpd_song_get_tag(song, MPD_TAG_TITLE, 0); */
  /* snprintf(str, CMDLENGTH, BLOCK_CRITICAL(ICON(ICON0), "%s"), title); */
}

void
musicc(int button)
{
  switch (button){
    case 1:
      break;
    case 2:
      break;
  }
}
