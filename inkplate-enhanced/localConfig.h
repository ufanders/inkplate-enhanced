typedef struct
{
  char wifiSsid[64];
  char wifiPass[64];
  char googlePhotosShareUrl[64];
  int localDownloadMax;
  int localUpdateInterval;
  int imageTransitionInterval;
} localConfig_t;

#include "Inkplate.h"

int localConfigInit(Inkplate *pInkplate);
void loadConfiguration(const char* filename, localConfig_t& config);
void saveConfiguration(const char* filename, const localConfig_t& config);
void printFile(const char* filename);