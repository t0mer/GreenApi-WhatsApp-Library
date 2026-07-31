<div align="center">

# GreenApi — WhatsApp for Arduino

**Send WhatsApp messages from your ESP32 or ESP8266 in a couple of lines of code.**

The GreenApi Arduino library wraps the [Green-API](https://green-api.com/en) service so you can send
WhatsApp messages without dealing with HTTPS requests or JSON formatting yourself.

<p>
  <img src="https://img.shields.io/badge/platform-ESP32%20%7C%20ESP8266-3C8DBC?logo=espressif&logoColor=white" alt="Platform: ESP32 | ESP8266">
  <img src="https://img.shields.io/github/v/release/t0mer/GreenApi-WhatsApp-Library?color=success&label=release" alt="Latest release">
  <img src="https://www.ardu-badge.com/badge/GreenApi.svg" alt="Arduino Library Manager">
  <img src="https://img.shields.io/github/license/t0mer/GreenApi-WhatsApp-Library?color=blue" alt="License: Apache-2.0">
</p>

</div>

---

## Table of Contents

- [Features](#features)
- [Supported boards](#supported-boards)
- [Installation](#installation)
- [Getting started](#getting-started)
  - [Set up a Green-API account](#set-up-a-green-api-account)
  - [Get contact and group IDs](#get-contact-and-group-ids)
- [Usage](#usage)
- [API reference](#api-reference)
- [Security note (TLS)](#security-note-tls)
- [License](#license)

---

## Features

- 📱 Send WhatsApp text messages to any contact or group.
- 🔌 Works on both **ESP32** and **ESP8266** from a single sketch.
- 🔒 HTTPS out of the box — no certificate provisioning required.
- 🧩 Tiny, dependency-free API: construct once, call `sendMessage()`.

## Supported boards

The library works on both **ESP32** and **ESP8266**. It automatically selects the correct
WiFi / HTTP client headers for the board you compile for, so the same sketch runs on either
chip — just include the matching WiFi header in your own sketch (`<WiFi.h>` for ESP32,
`<ESP8266WiFi.h>` for ESP8266).

## Installation

### Option A — Arduino Library Manager (recommended)

1. Open the Arduino IDE.
2. Go to **Sketch → Include Library → Manage Libraries…** (or click the 📚 icon in IDE 2.x).
3. Search for **GreenApi** and click **Install**.

### Option B — Manual install

1. Download the latest release from the [GitHub releases page](https://github.com/t0mer/GreenApi-WhatsApp-Library/releases).
2. Extract the downloaded ZIP file.
3. Move the extracted folder into the `libraries` directory of your Arduino sketchbook.
4. Restart the Arduino IDE.

---

## Getting started

### Set up a Green-API account

Navigate to [green-api.com](https://green-api.com/en) and register for a new account:

<div align="center"><img src="https://raw.githubusercontent.com/t0mer/GreenApi-WhatsApp-Library/main/screenshots/register.png" width="440" alt="Register"></div>

Fill in your details and click **Register**:

<div align="center"><img src="https://raw.githubusercontent.com/t0mer/GreenApi-WhatsApp-Library/main/screenshots/create_acoount.png" width="620" alt="Create account"></div>

Click **Create an instance**:

<div align="center"><img src="https://raw.githubusercontent.com/t0mer/GreenApi-WhatsApp-Library/main/screenshots/create_instance.png" width="640" alt="Create instance"></div>

Select the **Developer** instance (free):

<div align="center"><img src="https://raw.githubusercontent.com/t0mer/GreenApi-WhatsApp-Library/main/screenshots/developer_instance.png" width="640" alt="Developer instance"></div>

Copy the **Instance ID** and **Token** — you'll need them for the integration:

<div align="center"><img src="https://raw.githubusercontent.com/t0mer/GreenApi-WhatsApp-Library/main/screenshots/instance_details.png" width="640" alt="Instance details"></div>

Now link your WhatsApp with Green-API. In the left menu, under **API → Account**, click **QR**,
then copy the QR URL into your browser and click **Scan QR code**:

<div align="center"><img src="https://raw.githubusercontent.com/t0mer/GreenApi-WhatsApp-Library/main/screenshots/send_qr.png" width="640" alt="Send QR"></div>

<div align="center"><img src="https://raw.githubusercontent.com/t0mer/GreenApi-WhatsApp-Library/main/screenshots/scan_qr.png" width="640" alt="Scan QR"></div>

Scan the QR code to link your WhatsApp with Green-API:

<div align="center"><img src="https://raw.githubusercontent.com/t0mer/GreenApi-WhatsApp-Library/main/screenshots/qr.png" width="400" alt="QR code"></div>

Once linked, the instance header shows a green light indicating it is active:

<div align="center"><img src="https://raw.githubusercontent.com/t0mer/GreenApi-WhatsApp-Library/main/screenshots/active_instance.png" width="640" alt="Active instance"></div>

### Get contact and group IDs

Before sending messages, you need the recipient's ID. In the left menu, under
**API → Service methods**, click **getContacts**, then **Send**:

<div align="center"><img src="https://raw.githubusercontent.com/t0mer/GreenApi-WhatsApp-Library/main/screenshots/get_contacts.png" width="640" alt="Get contacts"></div>

You'll get back a list of contacts and groups:

- Contact IDs end with **`@c.us`**
- Group IDs end with **`@g.us`**

<div align="center"><img src="https://raw.githubusercontent.com/t0mer/GreenApi-WhatsApp-Library/main/screenshots/contacts_list.png" width="640" alt="Contacts list"></div>

Note down the ID you want to message — you'll pass it to `sendMessage()`.

---

## Usage

A minimal sketch that connects to WiFi and sends a WhatsApp message:

```cpp
#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>          // ESP32 WiFi library
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>   // ESP8266 WiFi library
#endif
#include <GreenApi.h>

const char* ssid          = "YourWiFiSSID";
const char* password      = "YourWiFiPassword";
const char* instanceId    = "YourInstanceId";
const char* instanceToken = "YourInstanceToken";
const char* target        = "11001234567@c.us";   // contact (@c.us) or group (@g.us)
const char* message       = "Hello, this is a test message from my new library!";

// Create an instance of the GreenApi class
GreenApi greenApi(instanceId, instanceToken);

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Connect to Wi-Fi
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi!");

  // Send the message
  Serial.println("Sending message...");
  String response = greenApi.sendMessage(target, message);
  Serial.println(response);
}

void loop() {
  // Your code here
}
```

> A ready-to-run version lives in [`examples/SendMessage`](examples/SendMessage/SendMessage.ino).

---

## API reference

### `GreenApi(const char* instanceId, const char* instanceToken)`

Creates a client bound to your Green-API instance. Copy both values from the Green-API console
(**Instance ID** and **Token**) exactly, with no leading or trailing spaces.

### `String sendMessage(const char* target, const char* message)`

Sends `message` to `target` and returns the raw HTTP response body from Green-API (or an error
string if the request could not be sent). `target` is the recipient ID — a contact ending in
`@c.us` or a group ending in `@g.us`.

---

## Security note (TLS)

For portability and zero setup, the library connects with certificate validation **disabled**
(`WiFiClientSecure::setInsecure()`). The connection is still encrypted, but the device does
**not** verify the server's identity. On a compromised or man-in-the-middle network an attacker
could intercept the TLS session and read the request — which includes your Green-API instance
token (in the URL) and the message contents.

This is a deliberate default: pinning a certificate in the library would break message sending
whenever Green-API rotates its certificate. If you need the device to reject invalid or forged
certificates, validate against Green-API's root CA instead of calling `setInsecure()`:

- **ESP32:** `client.setCACert(rootCA);` (PEM string of the root CA).
- **ESP8266:** use `BearSSL::WiFiClientSecure` with `client.setTrustAnchors(&cert);`
  (or `client.setFingerprint(...)`), keeping in mind a pinned fingerprint must be updated on
  every certificate rotation.

---

## License

Released under the [Apache License 2.0](LICENSE).
