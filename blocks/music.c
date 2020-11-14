#include <mpd/client.h>
#include <stdio.h>
#include "../util.h"
#include "music.h"

#define ICON0               ""

static void printstatus(char *str, struct mpd_connection *connection, enum mpd_state curstate);

void
printstatus(char *str, struct mpd_connection *connection, enum mpd_state curstate)
{
  if (curstate == MPD_STATE_STOP || curstate == MPD_STATE_UNKNOWN) {
    printempty(str);
  } else {
    struct mpd_song *song = mpd_run_current_song(connection);
    const char *title = mpd_song_get_tag(song, MPD_TAG_TITLE, 0);
    const char *artist = mpd_song_get_tag(song, MPD_TAG_ARTIST, 0);

    if (curstate == MPD_STATE_PAUSE)
      snprintf(str, CMDLENGTH, BLOCK_CRITICAL(ICON(ICON0), "%s - %s"), artist, title);
    else if (curstate == MPD_STATE_PLAY)
      snprintf(str, CMDLENGTH, BLOCK_NORM(ICON(ICON0), "%s - %s"), artist, title);

    mpd_song_free(song);
  }
}

void
musicu(char *str, int sigval, BlockData *blockdata)
{
  struct mpd_connection *connection = blockdata->mpd;
  enum mpd_error error = mpd_connection_get_error(blockdata->mpd);
  if (connection == NULL) {
    blockdata->mpd = creatempdconnection();
  } else if (error != MPD_ERROR_SUCCESS) {
    fprintf(stderr, "mpd: %s\n", mpd_connection_get_error_message(connection));
    if (!mpd_connection_clear_error(connection)) {
      mpd_connection_free(connection);
      blockdata->mpd = creatempdconnection();
      connection = blockdata->mpd;
    }
  }

  if (connection == NULL) {
    fprintf(stderr, "mpd: failed to reconnect\n");
    return;
  }

  if (!mpd_send_status(connection)) {
    fprintf(stderr, "mpd: failed to send status command\n");
    return;
  }

  // https://www.musicpd.org/doc/libmpdclient/structmpd__connection.html
  // when switching songs, it will often fail to receive status. this can be ignored
  struct mpd_status *status = mpd_recv_status(connection);
  if (status == NULL)
    return;

  enum mpd_state curstate = mpd_status_get_state(status);
  printstatus(str, blockdata->mpd, curstate);
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
