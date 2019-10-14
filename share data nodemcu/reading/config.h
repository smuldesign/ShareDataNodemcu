#define IO_USERNAME   "your_username"
#define IO_KEY        "your_key"

#define WIFI_SSID   "your_ssid"
#define WIFI_PASS   "your_pass"

#include "AdafruitIO_WiFi.h"

#if defined(USE_AIRLIFT) || defined(ADAFRUIT_METRO_M4_AIRLIFT_LITE)
  #if !defined(SPIWIFI_SS) 
    #define SPIWIFI SPI
    #define SPIWIFI_SS 10 
    #define NINA_ACK 9 
    #define NINA_RESETN 6
    #define NINA_GPIO0 -1
  #endif
  AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS, SPIWIFI_SS, NINA_ACK, NINA_RESETN, NINA_GPIO0, &SPIWIFI);
#else
  AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
#endif
