#include "GreenApi.h"

GreenApi::GreenApi(String instanceId, String instanceToken) {
  _instanceId = instanceId;
  _instanceToken = instanceToken;
  _urlBase = "https://api.green-api.com/waInstance" + _instanceId + "/sendMessage/" + _instanceToken;
}

void GreenApi::sendMessage(String target, String message) {
  HTTPClient http;
  String url = _urlBase;
  String payload = "{\"chatId\": \"" + target + "\", \"message\": \"" + message + "\"}";
  http.begin(url);
  http.addHeader("Content-Type", "application/json");
  
  int httpResponseCode = http.POST(payload);

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