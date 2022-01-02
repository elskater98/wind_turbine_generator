// Import required libraries
#include <Arduino.h>
#include <ESP8266WiFi.h>

// MCP23017 Lib
#include <Wire.h>
#include <Adafruit_MCP23017.h>

// MQTT Broker
#include "uMQTTBroker.h"
uMQTTBroker myBroker;

// Replace with your network credentials
const char* ssid = "ssid";
const char* password = "password";

// Instance of MCP23017 library
Adafruit_MCP23017 mcp;

int counter = 0;
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
  
  // Init LED (RED = [7,4], Yellow = [3,1], Green=[0])
  for(int i=0; i<8;i++){
     mcp.pinMode(i, OUTPUT);
  }
  
  //Serial.println("Starting MQTT broker");
  myBroker.init();
  myBroker.subscribe("#"); // all topics
  myBroker.subscribe("/temperature");
  myBroker.subscribe("/humidity");
  myBroker.subscribe("/acceleration");
}

void loop(){

  delay(5000); // 5 seconds
  
  myBroker.publish("broker/connections", (String)myBroker.getClientCount());
  
 // MQTT Broker LED BAR
 
  Serial.println((String)"Current Clients: " + myBroker.getClientCount());

  // Check if we have clients
  if(myBroker.getClientCount() > 0){
      for(int i=0; i < myBroker.getClientCount();i++){
      if(i<8){
        mcp.digitalWrite(i, HIGH);
      }
     }
  }else{
    for(int i = 0; i < 8 ;i++){
      mcp.digitalWrite(i, LOW);
    }
  } 
}
