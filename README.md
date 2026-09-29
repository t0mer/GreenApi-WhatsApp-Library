<div align="center">

# GreenApi — WhatsApp for Arduino

**Send WhatsApp messages from your ESP32 or ESP8266 in a couple of lines of code.**

The GreenApi Arduino library wraps the [Green-API](https://green-api.com/en) service so you can send
WhatsApp messages without dealing with HTTPS requests or JSON formatting yourself.

<p>
  <img src="https://img.shields.io/badge/platform-ESP32%20%7C%20ESP8266-3C8DBC?logo=espressif&logoColor=white" alt="Platform: ESP32 | ESP8266">
  <img src="https://img.shields.io/github/v/tag/t0mer/GreenApi-WhatsApp-Library?label=version" alt="Latest version">
  <img src="https://www.ardu-badge.com/badge/GreenApi.svg" alt="Arduino Library Manager">
  <img src="https://img.shields.io/github/license/t0mer/GreenApi-WhatsApp-Library?color=blue" alt="License: Apache-2.0">
</p>

</div>

---

## Table of Contents

- [Features](#features)
- [Supported boards](#supported-boards)
- [Requirements](#requirements)
- [Installation](#installation)
- [Getting started](#getting-started)
  - [Set up a Green-API account](#set-up-a-green-api-account)
  - [Get contact and group IDs](#get-contact-and-group-ids)
- [Usage](#usage)
- [Examples](#examples)
- [How it works](#how-it-works)
- [API reference](#api-reference)
- [Security notes](#security-notes)
- [Troubleshooting](#troubleshooting)
- [Contributing](#contributing)
- [License](#license)

---

## Features

- 📱 Send WhatsApp text messages to any contact or group.
- 🔌 Works on both **ESP32** and **ESP8266** from a single sketch.
- 🔒 HTTPS out of the box — no certificate provisioning required (see [Security notes](#security-notes)).
- 🧩 Tiny, dependency-free API: construct once, call `sendMessage()`. No JSON library needed.
- 🧾 Returns Green-API's raw response (or an error string) so your sketch can log or inspect it.

## Supported boards

The library works on both **ESP32** and **ESP8266** (`architectures=esp32,esp8266` in
`library.properties`). It automatically selects the correct WiFi / HTTP client headers for the
board you compile for, so the same sketch runs on either chip. `GreenApi.h` already pulls in the WiFi header, but you
may also include the matching one in your own sketch (`<WiFi.h>` for ESP32, `<ESP8266WiFi.h>`
for ESP8266), as the examples do.

Compiling for any other board stops with the error
`GreenApi supports only ESP32 and ESP8266 boards.`

## Requirements

- An **ESP32** or **ESP8266** board with the matching Arduino core installed
  ([ESP32 core](https://github.com/espressif/arduino-esp32) or
  [ESP8266 core](https://github.com/esp8266/Arduino)). The library uses only the core's
  `WiFiClientSecure` and `HTTPClient` — no third-party libraries.
- A WiFi network with internet access (your sketch is responsible for connecting to it).
- A [Green-API](https://green-api.com/en) account with an **authorized instance** (a WhatsApp
  account linked by QR code) — see [Getting started](#getting-started).

## Installation

### Option A — Arduino Library Manager (recommended)

1. Open the Arduino IDE.
2. Go to **Sketch → Include Library → Manage Libraries…** (or click the 📚 icon in IDE 2.x).
3. Search for **GreenApi** and click **Install**.

### Option B — PlatformIO

The library is published in the PlatformIO registry as `t0mer/GreenApi`. Add it to your
`platformio.ini`:

```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
lib_deps =
  t0mer/GreenApi@^1.1.0
```

### Option C — Manual install (ZIP)

1. Download the source ZIP of the latest version — the
   [`1.1.0` tag](https://github.com/t0mer/GreenApi-WhatsApp-Library/archive/refs/tags/1.1.0.zip)
   or **Code → Download ZIP** on the repository page.
   (The [GitHub releases page](https://github.com/t0mer/GreenApi-WhatsApp-Library/releases)
   currently only lists `1.0.0`, which is ESP32-only and whose `sendMessage()` returns nothing.)
2. In the Arduino IDE, choose **Sketch → Include Library → Add .ZIP Library…** and select the
   file — or extract it into the `libraries` folder of your Arduino sketchbook and restart the IDE.

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

Note down the ID you want to message — you'll pass it to `sendMessage()` exactly as shown
(the library does not add the `@c.us` / `@g.us` suffix for you).

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

## Examples

The library ships with two sketches, available in the Arduino IDE under
**File → Examples → GreenApi**:

| Example | What it does |
|---|---|
| [`SendMessage`](examples/SendMessage/SendMessage.ino) | Connects to WiFi, then sends one message to a contact. Works on ESP32 and ESP8266. **Start here.** |
| [`ExampleSketch`](examples/ExampleSketch/ExampleSketch.ino) | Minimal call syntax only. It does **not** connect to WiFi, so it will fail at runtime unless you add a WiFi connection first (as in `SendMessage`). |

Replace the `YourWiFiSSID`, `YourWiFiPassword`, `YourInstanceId`, `YourInstanceToken` and target
placeholders with your own values before uploading.

---

## How it works

Each `sendMessage()` call makes one blocking HTTPS request to Green-API's
[`sendMessage`](https://green-api.com/en/docs/api/sending/SendMessage/) method:

```text
POST https://api.green-api.com/waInstance{instanceId}/sendMessage/{instanceToken}
Content-Type: application/json

{"chatId": "<target>", "message": "<message>"}
```

The result is returned to your sketch and, when `Serial` is available (`if (Serial)`), also
printed: a successful response as `Response:` followed by the body, a transport failure as
`Error on sending POST: <code>`.

---

## API reference

### `GreenApi(const char* instanceId, const char* instanceToken)`

Creates a client bound to your Green-API instance. Copy both values from the Green-API console
(**Instance ID** and **Token**) exactly, with no leading or trailing spaces. The request URL is
built once, in the constructor, and always targets `https://api.green-api.com`.

### `String sendMessage(const char* target, const char* message)`

Sends `message` to `target` and returns a `String`:

| Outcome | Return value |
|---|---|
| The server answered (any HTTP status, including `4xx`/`5xx`) | The raw HTTP response body from Green-API. |
| The request could not be sent (no connection, DNS/TLS failure, …) | `"Error on sending POST: <code>"`, where `<code>` is the negative `HTTPClient` error code. |

| Parameter | Description |
|---|---|
| `target` | Recipient chat ID, passed as-is — a contact ending in `@c.us` (e.g. `11001234567@c.us`) or a group ending in `@g.us`. |
| `message` | Plain-text message body. It is inserted into the JSON payload **without escaping**, so avoid double quotes (`"`), backslashes (`\`) and raw newlines — see [Troubleshooting](#troubleshooting). |

The call is blocking and also prints the response (or error) to `Serial`. The device must already
be connected to WiFi.

---

## Security notes

- **TLS certificate validation is disabled.** For portability and zero setup, the library
  connects with `WiFiClientSecure::setInsecure()`. The connection is still encrypted, but the
  device does **not** verify the server's identity. On a compromised or man-in-the-middle network
  an attacker could intercept the TLS session and read the request — which includes your Green-API
  instance token (in the URL) and the message contents.

  This is a deliberate default: pinning a certificate in the library would break message sending
  whenever Green-API rotates its certificate. The secure client is created inside `sendMessage()`
  and there is currently no API to supply your own, so enabling validation means editing
  `src/GreenApi.cpp` and replacing the `setInsecure()` call with:

  - **ESP32:** `client.setCACert(rootCA);` (PEM string of Green-API's root CA).
  - **ESP8266:** `client.setTrustAnchors(&cert);` with a `BearSSL::X509List`
    (or `client.setFingerprint(...)`), keeping in mind a pinned fingerprint must be updated on
    every certificate rotation.
- **Credentials live in your sketch.** The instance ID, token and WiFi password are compiled
  into the firmware. Don't commit real values to a public repository, and treat anyone with
  access to the device's flash as able to read them. If a token leaks, regenerate it in the
  Green-API console.
- **Serial output.** Every response is printed to `Serial`; avoid leaving a serial console
  attached where others can read it if message contents are sensitive.

---

## Troubleshooting

- **`GreenApi supports only ESP32 and ESP8266 boards.`** — you are compiling for an unsupported
  board. Select an ESP32 or ESP8266 board in the IDE.
- **`Error on sending POST: -1`** (or another negative code) — the HTTPS request never reached
  Green-API. Make sure WiFi is connected *before* calling `sendMessage()` (the bundled
  `ExampleSketch` does not connect to WiFi) and that the network allows outbound HTTPS.
- **An error response from Green-API** (the returned body describes the problem) — check that the
  Instance ID and Token have no stray spaces, that the instance is authorized (green light in the
  console), and that the target ends in `@c.us` or `@g.us`.
- **Instance on a different API host.** Green-API assigns each instance an `apiUrl` (shown in the
  console). The library always sends to `https://api.green-api.com`, and Green-API warns that using
  a host not intended for the instance can break the integration
  ([Using GREEN-API hosts](https://green-api.com/en/docs/api/recommendations/using-green-api-hosts/)).
  If your console shows a different `apiUrl` and sending fails, note that the host isn't
  configurable in this library.
- **Message with quotes, backslashes or line breaks fails** — the message is not JSON-escaped.
  The JSON escape must reach the library literally, so in your C++ source write `\\\"` for a
  quote and `\\n` for a newline (e.g. `"Say \\\"hi\\\"\\nBye"`), or use a raw string literal
  such as `R"(Say \"hi\"\nBye)"`. Otherwise avoid those characters.

---

## Contributing

Issues and pull requests are welcome on
[GitHub](https://github.com/t0mer/GreenApi-WhatsApp-Library). Please test changes on both an
ESP32 and an ESP8266 board, and keep the public API backward compatible.

---

## License

Released under the [Apache License 2.0](LICENSE).
