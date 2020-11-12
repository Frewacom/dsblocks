#include <gio/gio.h>
#include <glib.h>
#include <stdio.h>

#include "kdeconnect.h"
#include "../util.h"

#define ICON0                           ""

#define PROPERTY_BUS_INTERFACE          "org.freedesktop.DBus.Properties"
#define PROPERTY_BUS_METHOD             "Get"

#define TARGET_BUS_NAME                 "org.kde.kdeconnect"
#define TARGET_BUS_OBJECT               "/modules/kdeconnect/devices/5b47b4994b69f3fc"
#define TARGET_BUS_DEVICE_INTERFACE     "org.kde.kdeconnect.device"
#define TARGET_BUS_BATTERY_INTERFACE    "org.kde.kdeconnect.device.battery"
#define TARGET_BUS_ISREACHABLE          "isReachable"
#define TARGET_BUS_BATTERY              "charge"

gboolean
isreachable(GDBusConnection *connection, GError *error)
{
  GVariant *response = g_dbus_connection_call_sync(
    connection,
    TARGET_BUS_NAME,
    TARGET_BUS_OBJECT,
    PROPERTY_BUS_INTERFACE,
    PROPERTY_BUS_METHOD,
    g_variant_new(
      "(ss)",
      TARGET_BUS_DEVICE_INTERFACE,
      TARGET_BUS_ISREACHABLE
    ),
    G_VARIANT_TYPE_TUPLE,
    G_DBUS_CALL_FLAGS_NONE,
    -1,
    NULL,
    &error
  );

  if (response == NULL || error != NULL) {
    printf("%s", error->message);
    return FALSE;
  }

  GVariant *methodresponse;
  gboolean reachable;
  g_variant_get(response, "(v)", &methodresponse);
  g_variant_get(methodresponse, "b", &reachable);

  g_variant_unref(response);
  g_variant_unref(methodresponse);

  return reachable;
}

gint32
getbattery(GDBusConnection *connection, GError *error)
{
  GVariant *response = g_dbus_connection_call_sync(
    connection,
    TARGET_BUS_NAME,
    TARGET_BUS_OBJECT,
    TARGET_BUS_BATTERY_INTERFACE,
    TARGET_BUS_BATTERY,
    NULL,
    G_VARIANT_TYPE_TUPLE,
    G_DBUS_CALL_FLAGS_NONE,
    -1,
    NULL,
    &error
  );

  if (response == NULL || error != NULL) {
    printf("%s\n", error->message);
    return -1;
  }

  gint32 charge;
  g_variant_get(response, "(i)", &charge);
  g_variant_unref(response);

  return charge;
}

void
kdeconnectu(char *str, int sigval)
{
  GError *error = NULL;
  GDBusConnection *connection = g_bus_get_sync(G_BUS_TYPE_SESSION, NULL, NULL);

  if (connection != NULL && isreachable(connection, error)) {
    gint32 charge = getbattery(connection, error);
    snprintf(str, CMDLENGTH, BLOCK_NORM(ICON(ICON0), "%d%%"), charge);
  } else {
    print_empty(str);
  }

  if (error != NULL)
    g_error_free(error);

  g_object_unref(connection);
}

void
kdeconnectc(int button)
{

}
