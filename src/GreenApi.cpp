#include "GreenApi.h"

GreenApi::GreenApi(const char* instanceId, const char* instanceToken) {
  _instanceId = instanceId;
  _instanceToken = instanceToken;
  _urlBase = "https://api.green-api.com/waInstance" + String(_instanceId) + "/sendMessage/" + String(_instanceToken);
}


void GreenApi::sendMessage(const char* target, const char* message) {
    // Create the payload as a String
    String payload = "{\"chatId\": \"" + String(target) + "\", \"message\": \"" + String(message) + "\"}";

    // Convert payload to const char* for use in HTTPClient
    const char* payloadChar = payload.c_str();

    HTTPClient http;
    http.begin(_urlBase);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(payloadChar);

    if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println("Response:");
        Serial.println(response);
    } else {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
    }

    http.end();
}