// Import required libraries
#include <Arduino.h>
#include <ESP8266WiFi.h>

//#include <SoftwareSerial.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include <SPI.h>
#include <SparkFun_ADXL345.h>

//MQTT Pub
#include <PubSubClient.h>

// Replace with your network credentials
const char* ssid = "ssid";
const char* password = "password";

LiquidCrystal_I2C lcd(0x27,16,2);

ADXL345 adxl = ADXL345();

// MQTT

const char* mqtt_server = "192.168.1.163"; // replace to your Broker IP
WiFiClient espClient;
PubSubClient client(espClient);

#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];

void callback(char* topic, byte* payload, unsigned int length) {
  /*Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();*/
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "DataProducer2";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "connected");
      // ... and resubscribe
      client.subscribe("#");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  
  // WIFI
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println(".");
  }
  
  // Print ESP8266 Local IP Address
  Serial.println(WiFi.localIP());
  
  Wire.begin(0, 2); // SDA and SCL
  // ACCELEROMETER
  adxl.powerOn();
               
  adxl.setRangeSetting(16);       //Definir el rango, valores 2, 4, 8 o 16

  // DISPLAY
  lcd.init();
  lcd.backlight();

  // MQTT
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop(){
    // MQTT
    if (!client.connected()) {
      reconnect();
    }
    client.loop();
      
    int x, y, z;
    adxl.readAccel(&x, &y, &z); 
    lcd.clear();
    
    lcd.print((String)"X:"+x+" Y:"+y+" Z:"+z);
    
    snprintf (msg, MSG_BUFFER_SIZE, "%f m/s",sqrt(x^2+y^2+z^2));
    client.publish("/acceleration", msg);
    delay(5000);
}
