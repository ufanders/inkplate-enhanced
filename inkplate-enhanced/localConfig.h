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
int loadConfiguration(const char* filename, localConfig_t& config);
int saveConfiguration(const char* filename, const localConfig_t& config);
int printFile(const char* filename);