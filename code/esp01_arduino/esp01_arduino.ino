// Import required libraries
#include <Arduino.h>
#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid = "ADAMO-C6CA";
const char* password = "JA54W6HGFCV7NC";

void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println(".");
  }

  // Print ESP8266 Local IP Address
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:

}
