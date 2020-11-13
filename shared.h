#include <limits.h>
#include <X11/Xlib.h>
#include <X11/Xresource.h>
#include <mpd/client.h>
#include <gio/gio.h>

#define CMDLENGTH                       75
#define NILL                            INT_MIN

typedef struct {
  Display *dpy;
  char *kdedbusobj;
  struct mpd_connection *mpd;
  GDBusConnection *dbus;
} BlockData;

extern Display *dpy;
extern pid_t pid;
