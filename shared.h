#pragma once
#include <limits.h>
#include <X11/Xlib.h>
#include <X11/Xresource.h>
#include <mpd/client.h>
#include <gio/gio.h>

#define CMDLENGTH                       50
#define NILL                            INT_MIN

typedef struct {
  Display *dpy;
  char *batteryobj;
  char *reachableobj;
  struct mpd_connection *mpd;
  enum mpd_state mpdstate;
  GDBusConnection *dbus;
} BlockData;

extern Display *dpy;
extern pid_t pid;
