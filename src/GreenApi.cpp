#include "GreenApi.h"

GreenApi::GreenApi(const char* instanceId, const char* instanceToken) {
  _instanceId = instanceId;
  _instanceToken = instanceToken;
  _urlBase = "https://api.green-api.com/waInstance" + String(_instanceId) + "/sendMessage/" + String(_instanceToken);
}

String GreenApi::sendMessage(const char* target, const char* message) {
    // Create the payload as a String
    String payload = "{\"chatId\": \"" + String(target) + "\", \"message\": \"" + String(message) + "\"}";
    const char* payloadChar = payload.c_str(); // Convert payload to const char* for use in HTTPClient

    HTTPClient http;
    http.begin(_urlBase); // Specify request destination
    http.addHeader("Content-Type", "application/json"); // Specify content-type header

    int httpResponseCode = http.POST(payloadChar); // Send the POST request

    String response; // Initialize an empty string to hold the response
    if (httpResponseCode > 0) {
        response = http.getString(); // Get the response payload as a string
        if (Serial) { // Check if Serial is available before printing
            Serial.println("Response:");
            Serial.println(response);
        }
    } else {
        response = "Error on sending POST: " + String(httpResponseCode); // Construct error message
        if (Serial) { // Check if Serial is available before printing
            Serial.println(response);
        }
    }

    http.end(); // Close the connection
    return response; // Return the full response or error message
}
