#include "wifiPortal.h"
#include <WiFiManager.h>

WiFiManager wm;
uint8_t portalRunning = 0;
String gPhotos_url = "https://photos.app.goo.gl/qvRVtQTixP6zCx3y9";

int wifiPortalInit(void)
{
  wm.setConfigPortalTimeout(WIFIPORTAL_TIMEOUT_SEC);

  /*
  // id/name, placeholder/prompt, default, length
  WiFiManagerParameter custom_param_1(
    "fld_gphotos_url", "Google Photos Share URL",
    gPhotos_url, 64);
  wifiManager.addParameter(&custom_param_1);

  WiFiManagerParameter custom_param_2(
    "fld_gphotos_numToPull", "Number of photos to pull at once",
    gPhotos_numToPull, 3);
  wifiManager.addParameter(&custom_param_2);

  WiFiManagerParameter custom_param_3(
    "fld_gphotos_updateIntervalAlbum", "Album Update Interval (days)",
    gPhotos_updateIntervalAlbum, 3);
  wifiManager.addParameter(&custom_param_3);

  WiFiManagerParameter custom_param_4(
    "fld_gphotos_updateIntervalImage", "Image Update Interval (hours)",
    gPhotos_updateIntervalImage, 4);
  wifiManager.addParameter(&custom_param_4);
  */
 
  return 0;
}

int wifiPortalStart(void)
{
    if (!wm.startConfigPortal("Inkplate10"))
    {
      Serial.println("Timed out.");
      //ESP.restart(); //reset and try again, or maybe put it to deep sleep
      portalRunning = 0;
      return 1;
    }

    portalRunning = 1;

    return 0;
}

int wifiPortalProcess(void)
{
  if(portalRunning) return wm.process();

  return 0;
}