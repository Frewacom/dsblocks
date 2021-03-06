#include <stdio.h>
#include <string.h>

#include "../util.h"
#include "battery.h"

#define ICONC                           "" /* error reading ACSTATEFILE */
#define ICON0                           "" /* no battery */
#define ICON1                           "" /* battery low */
#define ICON2                           "" /* battery intermediate 1 */
#define ICON3                           "" /* battery intermediate 2 */
#define ICON4                           "" /* battery full */
#define ICON5                           "" /* battery charging */

#define BATC                            10 /* critical level */
#define BATL                            20 /* low level */
#define BATP                            35 /* warn to plug in the charger at/below this level */
#define BATU                            95 /* warn to unplug the charger at/over this level */

#define BATCAPFILE                      "/sys/class/power_supply/BAT0/capacity"
#define ACSTATEFILE                     "/sys/class/power_supply/AC/online"
#define ADPSTATEFILE                    "/sys/class/power_supply/ADP1/online"
#define BATCFULLFILE                    "/sys/class/power_supply/BAT0/charge_full"
#define BATCNOWFILE                     "/sys/class/power_supply/BAT0/charge_now"
#define BATRATEFILE                     "/sys/class/power_supply/BAT0/current_now"

#define UNNOTIFY(t, msg) \
  uspawn((char *[]){ "/usr/bin/dunstify", "-r", "2120", "-t", t, "Battery Monitor", msg, NULL })
#define UCNOTIFY(t, msg) \
  uspawn((char *[]){ "/usr/bin/dunstify", "-r", "2120", "-t", t, "-u", "critical", "Battery Monitor", msg, NULL })
#define CNNOTIFY(t, msg) \
  cspawn((char *[]){ "/usr/bin/dunstify", "-r", "2120", "-t", t, "Battery Monitor", msg, NULL })
#define CCNOTIFY(t, msg) \
  cspawn((char *[]){ "/usr/bin/dunstify", "-r", "2120", "-t", t, "-u", "critical", "Battery Monitor", msg, NULL })

enum { Normal, Critical, Low, Plug, Unplug }; /* battery level */

void
batteryu(char *str, int ac, BlockData *blockdata)
{
  static int level = Normal;
  int bat;

  if (!readint(BATCAPFILE, &bat)) {
    printempty(str);
    return;
  }
  /* routine update */
  if (ac == NILL) {
    if (!readint(ACSTATEFILE, &ac) && !readint(ADPSTATEFILE, &ac)) {
      snprintf(str, CMDLENGTH, BLOCK_CRITICAL(ICON(ICONC), "%d%%"), bat);
      return;
    }
    if (ac) {
      if (bat < BATU) {
        if (level != Normal)
          level = Normal;
      } else if (level != Unplug) {
          level = Unplug;
      }
      snprintf(str, CMDLENGTH, BLOCK_SUCCESS(ICON(ICON5), "%d%%"), bat);
    } else {
      if (bat > BATP) {
        if (level != Normal)
          level = Normal;
        if (bat < BATU)
          snprintf(str, CMDLENGTH, BLOCK_NORM(ICON(ICON3), "%d%%"), bat);
        else
          snprintf(str, CMDLENGTH, BLOCK_NORM(ICON(ICON4), "%d%%"), bat);
      } else if (bat > BATL) {
        if (level != Plug) {
          level = Plug;
        }
        snprintf(str, CMDLENGTH, BLOCK_CRITICAL(ICON(ICON2), "%d%%"), bat);
      } else {
        if (bat > BATC) {
          if (level != Low) {
            level = Low;
          }
        } else if (level != Critical) {
          level = Critical;
        }
        snprintf(str, CMDLENGTH, BLOCK_CRITICAL(ICON(ICON1), "%d%%"), bat);
      }
    }
    /* charger plugged in */
  } else if (ac) {
    if (bat < BATU) {
      if (level != Normal)
        level = Normal;
    } else {
      level = Unplug;
    }
    snprintf(str, CMDLENGTH, BLOCK_SUCCESS(ICON(ICON5), "%d%%"), bat);
    /* charger plugged out */
  } else {
    if (bat > BATP) {
      if (level != Normal)
        level = Normal;
      if (bat < BATU)
        snprintf(str, CMDLENGTH, BLOCK_NORM(ICON(ICON3), "%d%%"), bat);
      else
        snprintf(str, CMDLENGTH, BLOCK_NORM(ICON(ICON4), "%d%%"), bat);
    } else if (bat > BATL) {
      level = Plug;
      snprintf(str, CMDLENGTH, BLOCK_CRITICAL(ICON(ICON2), "%d%%"), bat);
    } else {
      if (bat > BATC) {
        if (level != Low) {
          level = Low;
        }
      } else if (level != Critical) {
        level = Critical;
      }
      snprintf(str, CMDLENGTH, BLOCK_CRITICAL(ICON(ICON1), "%d%%"), bat);
    }
  }
}

void
batteryc(int button, BlockData *blockdata)
{
  int ac;
  int cur, rate;
  int hr, mn;

  if (!readint(ACSTATEFILE, &ac) && !readint(ADPSTATEFILE, &ac)) {
    return;
  }
  if (ac) {
    int cnow;

    if (!readint(BATCFULLFILE, &cur)) {
      return;
    }
    if (!readint(BATCNOWFILE, &cnow)) {
      return;
    }
    cur -= cnow;
  } else
    if (!readint(BATCNOWFILE, &cur)) {
      return;
    }
  if (!readint(BATRATEFILE, &rate)) {
    return;
  }
  if (!rate) {
    return;
  }
  hr = cur / rate;
  mn = ((cur * 60) / rate) - hr * 60;
  switch (hr) {
    case 0:
      switch (mn) {
        case 0:
          CNNOTIFY("2000", "Battery fully charged");
          break;
        case 1:
          CNNOTIFY("2000", "1 minute remaining");
          break;
        default:
          {
            char buf[21];

            snprintf(buf, sizeof buf, "%d minutes remaining", mn);
            CNNOTIFY("2000", buf);
          }
          break;
      }
      break;
    case 1:
      switch (mn) {
        case 0:
          CNNOTIFY("2000", "1 hour remaining");
          break;
        case 1:
          CNNOTIFY("2000", "1 hour, 1 minute remaining");
          break;
        default:
          {
            char buf[29];

            snprintf(buf, sizeof buf, "1 hour, %d minutes remaining", mn);
            CNNOTIFY("2000", buf);
          }
          break;
      }
      break;
    default:
      switch (mn) {
        case 0:
          {
            char buf[19];

            snprintf(buf, sizeof buf, "%d hours remaining", hr);
            CNNOTIFY("2000", buf);
          }
          break;
        case 1:
          {
            char buf[29];

            snprintf(buf, sizeof buf, "%d hours, 1 minute remaining", hr);
            CNNOTIFY("2000", buf);
          }
          break;
        default:
          {
            char buf[31];

            snprintf(buf, sizeof buf, "%d hours, %d minutes remaining", hr, mn);
            CNNOTIFY("2000", buf);
          }
          break;
      }
      break;
  }
}
