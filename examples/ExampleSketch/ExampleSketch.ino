#include <GreenApi.h>

GreenApi greenApi("YourInstanceID", "YourInstanceToken");

void setup() {
  Serial.begin(115200);
  // Wait for serial monitor to open
  while (!Serial);

  greenApi.sendMessage("YourChatId", "Hello, this is a test message from my new library!");
}

void loop() {
  // Your code here
}