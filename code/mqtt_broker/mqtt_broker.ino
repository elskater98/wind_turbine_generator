// Import required libraries
#include <Arduino.h>
#include <ESP8266WiFi.h>

// MCP23017 Lib
#include <Wire.h>
#include <Adafruit_MCP23017.h>

// Replace with your network credentials
const char* ssid = "ADAMO-C6CA";
const char* password = "JA54W6HGFCV7NC";

// Instance of MCP23017 library
Adafruit_MCP23017 mcp;

void setup(){

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
  
  //MCP
  mcp.begin(); //0x20
  
  //Red
  mcp.pinMode(7, OUTPUT);
  mcp.pinMode(6, OUTPUT);
  mcp.pinMode(5, OUTPUT);
  mcp.pinMode(4, OUTPUT);
  // Yellow
  mcp.pinMode(3, OUTPUT);
  mcp.pinMode(2, OUTPUT);
  mcp.pinMode(1, OUTPUT);

  // Green
  mcp.pinMode(0, OUTPUT);
  
}

void loop(){
  Serial.println("Switch LED on");
  
  // red
  mcp.digitalWrite(7, HIGH);
  mcp.digitalWrite(6, HIGH);
  mcp.digitalWrite(5, HIGH);
  mcp.digitalWrite(4, HIGH);
  delay(1000);

  // yellow
  mcp.digitalWrite(3, HIGH);
  mcp.digitalWrite(2, HIGH);
  mcp.digitalWrite(1, HIGH);
  delay(2000);

  // green
  mcp.digitalWrite(0, HIGH);
  delay(3000);
  
  
  
  // red
  Serial.println("Switch LED off");
  mcp.digitalWrite(7, LOW);
  mcp.digitalWrite(6, LOW);
  mcp.digitalWrite(5, LOW);
  mcp.digitalWrite(4, LOW);
  delay(2000);

  // yellow
  mcp.digitalWrite(3, LOW);
  mcp.digitalWrite(2, LOW);
  delay(1000);

  // green
  mcp.digitalWrite(1, LOW);
  mcp.digitalWrite(0, LOW);
    
}
