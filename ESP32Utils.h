#ifndef ESP32UTILS_H
#define ESP32UTILS_H

#include <Arduino.h>

class ESP32Utils {
  public:
    ESP32Utils();
    void initWiFi(char* ssid, char* password);
    void initOTA();
  private:
    int _a;
};

#endif
