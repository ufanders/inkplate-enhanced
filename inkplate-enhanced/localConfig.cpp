#include "localConfig.h"
#include <ArduinoJson.h>

SdFile folder, file;

int localConfigInit(Inkplate *pInkplate)
{
    if(pInkplate->sdCardInit()) return 0; //success.
    
    return 1; //failure.
}

int loadConfiguration(const char* filename, localConfig_t& config)
{
    // Open file for reading
    bool r = file.open(filename, O_READ);
    if(!r) return 1; //failure.

    // Allocate a temporary JsonDocument
    JsonDocument doc;
  
    // Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, file);
    if (error)
      Serial.println(F("Failed to read file, using default configuration"));
  
    // Copy values from the JsonDocument to the Config
    strlcpy(config.wifiSsid, // <- destination
            doc["wifiSsid"] | "MY_SSID", // <- source
            sizeof(config.wifiSsid)); // <- destination's capacity
  
    strlcpy(config.wifiPass, doc["wifiPass"] | 
      "MY_PASSWORD", sizeof(config.wifiPass));

    strlcpy(config.googlePhotosShareUrl, doc["googlePhotosShareUrl"] | 
      "MY_GOOGLEPHOTOSSHAREURL", sizeof(config.googlePhotosShareUrl));

    // Close the file (Curiously, File's destructor doesn't close the file)
    file.close();

    return 0;
  }

int saveConfiguration(const char* filename, const localConfig_t& config)
{
  bool r;
  char newFn[12+1]; strncpy(newFn, filename, 8); strcpy(&newFn[strlen(filename)-4], ".old");
  //file.remove(newFn); //remove previous backup.
  //file.rename(filename, newFn); //create new backup.
  // rename existing file, otherwise the configuration is appended to the file

  // Open file for writing
  r = file.open(filename, O_WRITE);
  if (!r) {
    Serial.println(F("Failed to create file"));
    return 1;
  }

  JsonDocument doc; // Allocate a temporary JsonDocument

  // Set the values in the document
  doc["wifiSsid"] = config.wifiSsid;
  doc["wifiPass"] = config.wifiPass;
  doc["googlePhotosShareUrl"] = config.googlePhotosShareUrl;

  // Serialize JSON to file
  if (serializeJson(doc, file) == 0) {
    Serial.println(F("Failed to write to file"));
    return 1;
  }

  r = file.close();

  if(r) return 0;
  return 1;
}

// Prints the content of a file to the Serial
int printFile(const char* filename)
{
  // Open file for reading
  bool r = file.open(filename);
  if (!r) {
    Serial.println(F("Failed to read file"));
    return 1;
  }

  // Extract each characters by one by one
  while (file.available()) {
    Serial.print((char)file.read());
  }
  Serial.println();

  r = file.close();

  if(r) return 0;
  return 1;
}

