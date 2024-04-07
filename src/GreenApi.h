#ifndef GreenApi_h
#define GreenApi_h

#include <Arduino.h>    // Include Arduino.h before other headers
#include <HTTPClient.h>

class GreenApi {
  public:
    GreenApi(const char* instanceId, const char* instanceToken);
    void sendMessage(const char* target, const char* message); // Remove extra qualification
  private:
    String _urlBase;
    const char* _instanceId;    
    const char* _instanceToken;
};



#endif