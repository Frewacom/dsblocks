#include <mpd/client.h>
#include <stdio.h>
#include "../util.h"
#include "music.h"

#define ICON0                           ""
#define NCMPCPP                         (char *[]){ "/usr/bin/ncmpcpp", NULL }

static unsigned int isconnected(BlockData *blockdata);
static void printstatus(char *str, BlockData *blockdata, enum mpd_state curstate);

unsigned int
isconnected(BlockData *blockdata)
{
  struct mpd_connection *connection = blockdata->mpd;
  enum mpd_error error = mpd_connection_get_error(connection);
  if (connection == NULL) {
    blockdata->mpd = creatempdconnection();
  } else if (error != MPD_ERROR_SUCCESS) {
    fprintf(stderr, "mpd: %s\n", mpd_connection_get_error_message(connection));
    if (!mpd_connection_clear_error(connection)) {
      mpd_connection_free(connection);
      blockdata->mpd = creatempdconnection();
    }
  }

  if (connection == NULL) {
    fprintf(stderr, "mpd: failed to reconnect\n");
    return 0;
  }

  return 1;
}

void
printstatus(char *str, BlockData *blockdata, enum mpd_state curstate)
{
  if (curstate == MPD_STATE_STOP || curstate == MPD_STATE_UNKNOWN) {
    printempty(str);
  } else {
    struct mpd_song *song = mpd_run_current_song(blockdata->mpd);
    const char *title = mpd_song_get_tag(song, MPD_TAG_TITLE, 0);
    const char *artist = mpd_song_get_tag(song, MPD_TAG_ARTIST, 0);

    if (curstate == MPD_STATE_PAUSE)
      snprintf(str, CMDLENGTH, BLOCK_CRITICAL(ICON(ICON0), "%s - %s"), artist, title);
    else if (curstate == MPD_STATE_PLAY)
      snprintf(str, CMDLENGTH, BLOCK_NORM(ICON(ICON0), "%s - %s"), artist, title);

    blockdata->mpdstate = curstate;
    mpd_song_free(song);
  }
}

void
musicu(char *str, int sigval, BlockData *blockdata)
{
  if (!isconnected(blockdata)) {
    printempty(str);
    return;
  }

  if (!mpd_send_status(blockdata->mpd)) {
    fprintf(stderr, "mpd: failed to send status command\n");
    return;
  }

  // https://www.musicpd.org/doc/libmpdclient/structmpd__connection.html
  // when switching songs, it will often fail to receive status. this can be ignored
  struct mpd_status *status = mpd_recv_status(blockdata->mpd);
  if (status == NULL)
    return;

  enum mpd_state curstate = mpd_status_get_state(status);
  printstatus(str, blockdata, curstate);
  mpd_status_free(status);
}

void
musicc(int button, BlockData *blockdata)
{
  if (!isconnected(blockdata))
    return;

  switch (button) {
    case 1:
      mpd_run_pause(blockdata->mpd, blockdata->mpdstate != MPD_STATE_PAUSE);
      break;
    case 2:
      break;
  }
}
