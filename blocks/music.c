#include <mpd/client.h>
#include <stdio.h>
#include "../util.h"
#include "music.h"

#define ICON0               ""

void
musicu(char *str, int sigval, BlockData *blockdata)
{
  if (blockdata->mpd == NULL || !mpd_send_status(blockdata->mpd)) {
    return;
  }

  struct mpd_status *status = mpd_recv_status(blockdata->mpd);
  enum mpd_state curstate = mpd_status_get_state(status);

  if (curstate == MPD_STATE_STOP || curstate == MPD_STATE_UNKNOWN) {
    printempty(str);
  } else {
    struct mpd_song *song = mpd_run_current_song(blockdata->mpd);
    const char *title = mpd_song_get_tag(song, MPD_TAG_TITLE, 0);

    switch (curstate) {
      case MPD_STATE_PAUSE:
        snprintf(str, CMDLENGTH, BLOCK_CRITICAL(ICON(ICON0), "%s"), title);
        break;
      case MPD_STATE_PLAY:
        snprintf(str, CMDLENGTH, BLOCK_NORM(ICON(ICON0), "%s"), title);
        break;
      default:
        return;
    }

    mpd_song_free(song);
  }

  mpd_status_free(status);
}

void
musicc(int button, BlockData *blockdata)
{
  switch (button){
    case 1:
      break;
    case 2:
      break;
  }
}
