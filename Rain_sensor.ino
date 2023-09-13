#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "Replace with your ID"
#define BLYNK_TEMPLATE_NAME "Replace with your template name"
#define BLYNK_AUTH_TOKEN "Replace with your token"
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// WiFi credentials
const char* ssid = " Replace with your Wifi name";
const char* pass = "Replace with your Wifi password";

// esp32 pins configurations
const int humiditySensorPin = 12;
const int temperatureSensorPin = 13;
const int ledPin = 14;

// Virtual pins in the Blynk app
const int virtualHumidityPin = V0;
const int virtualTemperaturePin = V1;
const int virtualLEDpin= V2;


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
  pinMode(humiditySensorPin, INPUT);
  pinMode(temperatureSensorPin, INPUT);
}

void loop() {
  Humidity();
  Temperature();
  Blynk.run();
  
  if(analogRead(humiditySensorPin)> 80 && analogRead(temperatureSensorPin)< 40)
  {
    Serial.println("Expected rain");
    digitalWrite(ledPin,HIGH);
    Blynk.virtualWrite(virtualLEDpin, HIGH);
  }
  else if(analogRead(humiditySensorPin)> 80 && analogRead(temperatureSensorPin)< 40)
  {
    Serial.println("No chances of rain");
    digitalWrite(ledPin,HIGH);
    Blynk.virtualWrite(virtualLEDpin, LOW);
  }
}

// Function to send Humidity value to Blynk virtual pin
void Humidity() 
{
  Blynk.virtualWrite(virtualHumidityPin,analogRead(humiditySensorPin));  //Sending humidity value to virtual Humidity pin
}

//Function to send temperature value to Blynk virtual pin
void Temperature()
{
  Blynk.virtualWrite(virtualTemperaturePin,analogRead(temperatureSensorPin));  //Sendinng temperature value to virtual temperature pin
}

//Controlling the LED manually through Blynk app
BLYNK_WRITE(virtualLEDpin) {
  int pinValue = param.asInt(); // Read the state of the Blynk Button widget on Virtual Pin V2
  Serial.println(pinValue);
  if (pinValue == 1) {
    digitalWrite(ledPin, HIGH); // Turn the LED ON
  } 
  else
  {
    digitalWrite(ledPin, LOW); // Turn the LED OFF
  }
}
