/*
Inkplate-Enhanced goals:
1. SoftAP for WiFi configuration.
2. Wake button:
a. press to advance image.
b. hold 5s to update Google Photos image cache.
c. hold 10s to engage Wifi Config.
3. Config text file on SD card containing:
a. GOOGLE_PHOTO_SHARE_LINK URL, also shadowed in program memory in case SD card is absent.
b. Number photos to download within an update.
c. GPhotos local image cache update interval.
d. Image transition interval in seconds.
e. Help text file on SD card explaining all fields/units/limits in config file.
4. Download GPhotos from album specified to SD card.
5. Provide on-screen indication of:
a. Update download status/progress.
b. Power off status.
c. Button hold feedback (update photos, launch WiFiManager).
d. Image loading.
e. Low battery.

ESP32-WROOM-E-N4R8: 4MB Flash, 520KB SRAM, 8MB PSRAM, 240MHz.
Expected WiFi throughput 15Mbps/1.88MBps.
Expected image size ~4MB.
Inkplate10 example Image_frame_from_web: flash/ram usage = 31%/18%.
Inkplate10 example Image_frame_from_sd: flash/ram usage = 21%/14%.

ImageMagick CLI command: "Radek-Inkplate-NYC % mogrify -resize 1200x825^ -gravity center -extent 1200x825 -path ../Radek-Inkplate-NYC-out *.jpg"

Libraries:
1. https://github.com/SolderedElectronics/Inkplate-Arduino-library
2. https://github.com/rlogiacco/BatterySense
3. https://github.com/tzapu/WiFiManager

*/
#include "wifiPortal.h"

/*
class IntParameter : public WiFiManagerParameter {
public:
    IntParameter(const char *id, const char *placeholder, long value, const uint8_t length = 10)
        : WiFiManagerParameter("") {
        init(id, placeholder, String(value).c_str(), length, "", WFM_LABEL_BEFORE);
    }

    long getValue() {
        return String(WiFiManagerParameter::getValue()).toInt();
    }
};
*/

struct Settings {
  int i;
  char s[20];
} set;

void setup() {
  wifiPortalInit();
  wifiPortalStart();
}

void loop() {
  wifiPortalProcess();
}
