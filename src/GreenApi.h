#ifndef GreenApi_h
#define GreenApi_h

#include <Arduino.h>    // Include Arduino.h before other headers

// Board-specific WiFi / HTTP client headers. This library supports both
// ESP32 and ESP8266; the two cores name these headers differently.
#if defined(ESP32)
  #include <WiFi.h>
  #include <WiFiClientSecure.h>
  #include <HTTPClient.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <WiFiClientSecure.h>
  #include <ESP8266HTTPClient.h>
#else
  #error "GreenApi supports only ESP32 and ESP8266 boards."
#endif

class GreenApi {
  public:
    GreenApi(const char* instanceId, const char* instanceToken);
    String sendMessage(const char* target, const char* message); // Remove extra qualification
  private:
    String _urlBase;
    const char* _instanceId;
    const char* _instanceToken;
};

#endif
