#include "wifiPortal.h"
#include <WiFiManager.h>

WiFiManager wm;
uint8_t portalRunning = 0;

int wifiPortalStart(void)
{
    wm.setConfigPortalTimeout(WIFIPORTAL_TIMEOUT_SEC);

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