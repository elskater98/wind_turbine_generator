// Import required libraries
#include <Arduino.h>
#include <ESP8266WiFi.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>

//MQTT Pub
#include <PubSubClient.h>

// Replace with your network credentials
const char* ssid = "ssid";
const char* password = "password";

// DHT11
#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE    DHT11     // DHT 11

DHT dht(DHTPIN, DHTTYPE);

float t = 0.0;
float h = 0.0;

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
    String clientId = "DataProducer1";
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
  
  dht.begin();

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void clean_screen()
{
  Serial.write(0x7C);
  Serial.write(0x00);
}
 
void loop(){
    clean_screen();

    // MQTT
      if (!client.connected()) {
        reconnect();
      }
      client.loop();
    
    // Temperature
    float newT = dht.readTemperature();
    if (isnan(newT)) {
      Serial.println("Failed to read from DHT sensor!");
    }
    else {
      t = newT;
      String outStringT = (String) t+"C ";
      Serial.print(outStringT);
      snprintf (msg, MSG_BUFFER_SIZE, "%f ºC", t);
      client.publish("/temperature", msg);
    }
    
    // Humidity
    float newH = dht.readHumidity();
    // if humidity read failed, don't change h value 
    if (isnan(newH)) {
      Serial.println("Failed to read from DHT sensor!");
    }
    else {
      h = newH;
      String outStringH = (String) h+"%"; 
      Serial.print(outStringH);
      snprintf (msg, MSG_BUFFER_SIZE, "%f ", h);
      client.publish("/humidity", msg);
    }

    delay(5000);
}
