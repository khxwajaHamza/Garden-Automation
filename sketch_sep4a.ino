#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6-84XrfXm"
#define BLYNK_TEMPLATE_NAME "ESP32 LED Blink"
#define BLYNK_AUTH_TOKEN "ew1oNdCnwdFcj9xKuHVkrcg-rsq6Rkzh"
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// WiFi credentials
const char* ssid = "Alpha Realtors Pvt. Ltd.";
const char* pass = "1212@Alpha";

const int ledPin = 2;

BlynkTimer timer;

void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);

  // Connect to Wi-Fi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  // Configure Blynk with your authentication token
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Setup a timed function to update the LED state
  //timer.setInterval(1000L, BLYNK_WRITE);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  Blynk.run();
 // timer.run();
}

BLYNK_WRITE(V0) {
  int pinValue = param.asInt(); // Read the state of the Blynk Button widget on Virtual Pin V1
  Serial.println(pinValue);
  if (pinValue == 1) {
    digitalWrite(ledPin, HIGH); // Turn the LED ON
  } 
  else
  {
    digitalWrite(ledPin, LOW); // Turn the LED OFF
  }
}
