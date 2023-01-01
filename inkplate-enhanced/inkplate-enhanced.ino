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
#define pinWake GPIO_NUM_36

void setup() {
  pinMode(pinWake, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

}

int taskButton(int pin, uint8_t *pStageOut)
{
  uint32_t tStart = millis();
  uint32_t tStop = 0;
  uint8_t stage = 0;
  uint8_t doUpdate = 0;

  while(tStop == 0) //loop until button released.
  {
    if(digitalRead(pin))
    {
      tStop = millis();
    }
    else
    {
      switch(stage) //quantize how long button is held into 2 stages.
      {
        case 0:
          if(millis() - tStart > 5000) stage = 1;
          doUpdate = 1;
        break;

        case 1:
          if(millis() - tStart > 10000) stage = 2;
          doUpdate = 1;
        break;

        default: break;
      }
      
      if(doUpdate) //show a notice on the display.
      {
        switch(stage)
        {
          case 1:
            //TODO: draw notice "release to update photos".
          break;

          case 2:
            //TODO: draw notice "release to change settings".
          break;

          default: break;
        }

        doUpdate = 0;
      }
    }
  }

  pStageOut = *stage;
  return 0;
}
