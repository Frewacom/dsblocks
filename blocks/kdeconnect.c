#include <gio/gio.h>
#include <glib.h>
#include <stdio.h>

#include "../util.h"
#include "kdeconnect.h"

#define ICON0                           ""

#define PROPERTY_BUS_INTERFACE          "org.freedesktop.DBus.Properties"
#define PROPERTY_BUS_METHOD             "Get"

#define TARGET_BUS_NAME                 "org.kde.kdeconnect"
#define TARGET_BUS_DEVICE_INTERFACE     "org.kde.kdeconnect.device"
#define TARGET_BUS_BATTERY_INTERFACE    "org.kde.kdeconnect.device.battery"
#define TARGET_BUS_ISREACHABLE          "isReachable"
#define TARGET_BUS_BATTERY              "charge"
#define TARGET_BUS_BATTERY_CHARGING     "isCharging"

static gboolean isreachable(GDBusConnection *connection, GError *error, const char *obj);
static gint32 getbattery(GDBusConnection *connection, GError *error, const char *obj);

gboolean
isreachable(GDBusConnection *connection, GError *error, const char *obj)
{
  GVariant *response = g_dbus_connection_call_sync(
    connection,
    TARGET_BUS_NAME,
    obj,
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
    printf("%s\n", error->message);
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
getbattery(GDBusConnection *connection, GError *error, const char *obj)
{
  GVariant *response = g_dbus_connection_call_sync(
    connection,
    TARGET_BUS_NAME,
    obj,
    PROPERTY_BUS_INTERFACE,
    PROPERTY_BUS_METHOD,
    g_variant_new(
      "(ss)",
      TARGET_BUS_BATTERY_INTERFACE,
      TARGET_BUS_BATTERY
    ),
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

  GVariant *methodresponse;
  gint32 charge;
  g_variant_get(response, "(v)", &methodresponse);
  g_variant_get(methodresponse, "i", &charge);

  g_variant_unref(response);
  g_variant_unref(methodresponse);

  return charge;
}

gboolean
getcharging(GDBusConnection *connection, GError *error, const char *obj)
{
  GVariant *response = g_dbus_connection_call_sync(
    connection,
    TARGET_BUS_NAME,
    obj,
    PROPERTY_BUS_INTERFACE,
    PROPERTY_BUS_METHOD,
    g_variant_new(
      "(ss)",
      TARGET_BUS_BATTERY_INTERFACE,
      TARGET_BUS_BATTERY_CHARGING
    ),
    G_VARIANT_TYPE_TUPLE,
    G_DBUS_CALL_FLAGS_NONE,
    -1,
    NULL,
    &error
  );

  if (response == NULL || error != NULL) {
    printf("%s\n", error->message);
    return FALSE;
  }

  GVariant *methodresponse;
  gboolean charging;
  g_variant_get(response, "(v)", &methodresponse);
  g_variant_get(methodresponse, "b", &charging);

  g_variant_unref(response);
  g_variant_unref(methodresponse);

  return charging;
}

void
kdeconnectu(char *str, int sigval, BlockData *blockdata)
{
  if (blockdata->dbus == NULL) {
    blockdata->dbus = createdbusconnection();

    if (blockdata->dbus == NULL)
      return;
  }

  GError *error = NULL;

  if (blockdata->dbus != NULL && isreachable(blockdata->dbus, error, blockdata->reachableobj)) {
    gint32 charge = getbattery(blockdata->dbus, error, blockdata->batteryobj);
    gboolean charging = getcharging(blockdata->dbus, error, blockdata->batteryobj);

    if (charging) {
      snprintf(str, CMDLENGTH, BLOCK_SUCCESS(ICON(ICON0), "%d%%"), charge);
    } else {
      snprintf(str, CMDLENGTH, BLOCK_NORM(ICON(ICON0), "%d%%"), charge);
    }
  } else {
    printempty(str);
  }

  if (error != NULL)
    g_error_free(error);
}

void
kdeconnectc(int button, BlockData *blockdata)
{

}
