#ifndef GreenApi_h
#define GreenApi_h

#include <Arduino.h>    // Include Arduino.h before other headers
#include <HTTPClient.h>

class GreenApi {
  public:
    GreenApi(const char* instanceId, const char* instanceToken);
    void sendMessage(const char* target, const char* message);
  private:
    String _urlBase;
    const char* _instanceId;    // Changed to const char* for better memory management
    const char* _instanceToken; // Changed to const char* for better memory management
};

#endif