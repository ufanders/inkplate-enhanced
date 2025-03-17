#include "localConfig.h"
#include "Inkplate.h"

SdFile folder, file;

int localConfigInit(Inkplate *pInkplate)
{
    if(pInkplate->sdCardInit()) return 0; //success.
    
    return 1: //failure.
}

void loadConfiguration(const char* filename, localConfig_t& config) {
    // Open file for reading
    int r = folder.open("/");

  
    // Allocate a temporary JsonDocument
    JsonDocument doc;
  
    // Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, file);
    if (error)
      Serial.println(F("Failed to read file, using default configuration"));
  
    // Copy values from the JsonDocument to the Config
    config.port = doc["port"] | 2731;
    strlcpy(config.hostname,                  // <- destination
            doc["hostname"] | "example.com",  // <- source
            sizeof(config.hostname));         // <- destination's capacity
  
    // Close the file (Curiously, File's destructor doesn't close the file)
    file.close();
  }

  void saveConfiguration(const char* filename, const localConfig_t& config) {
    // Delete existing file, otherwise the configuration is appended to the file
    folder.remove(filename);
  
    // Open file for writing
    file = folder.open(filename, FILE_WRITE);
    if (!file) {
      Serial.println(F("Failed to create file"));
      return;
    }
  
    // Allocate a temporary JsonDocument
    JsonDocument doc;
  
    // Set the values in the document
    doc["hostname"] = config.hostname;
    doc["port"] = config.port;
  
    // Serialize JSON to file
    if (serializeJson(doc, file) == 0) {
      Serial.println(F("Failed to write to file"));
    }
  
    // Close the file
    file.close();
  }
  
  // Prints the content of a file to the Serial
  void printFile(const char* filename) {
    // Open file for reading
    file = folder.open(filename);
    if (!file) {
      Serial.println(F("Failed to read file"));
      return;
    }
  
    // Extract each characters by one by one
    while (file.available()) {
      Serial.print((char)file.read());
    }
    Serial.println();
  
    // Close the file
    file.close();
  }

