//Libraries
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Constants
WiFiClient espClient;
PubSubClient client(espClient);

// MQTT
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
const char* mqtt_server = "192.168.1.163"; // change

// Wi-Fi
const char* ssid = "ADAMO-C6CA";
const char* password = "JA54W6HGFCV7NC";
String response;

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]); // Gather data from broker
  }
  Serial.println();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "AT";
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

void setup() {
  
  Serial.begin(115200);
  
  /*WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println(WiFi.localIP());*/
  
  /*client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  client.subscribe("#");*/
  
}

void loop() {

   if(Serial.available() > 0){
    response="Response Data";
    Serial.write("R");
   }
   
  /*if (!client.connected()) {
    reconnect();
  }
  client.loop();*/
  
  delay(1000);
}
