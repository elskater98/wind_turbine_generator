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
// Replace with your network credentials
const char* ssid = "ssid";
const char* password = "password";

// Data
char temp[32];
char hum[32];
char acc[32];

void callback(char* topic, byte* payload, unsigned int length) {

  // Temperature /temperature
  if((char)topic[1] == 't'){
            for (int i = 0; i < 5; i++) {
          temp[i] = (char)payload[i];
      }
      temp[5]='t';
  }

  // Humidity
   if((char)topic[1] == 'h'){
            for (int i = 0; i < 5; i++) {
          hum[i] = (char)payload[i];
      }
      hum[5]='h';
   }
  // Acceleration 
  if((char)topic[1] == 'a'){
            for (int i = 0; i < 6; i++) {
        acc[i] = (char)payload[i];
    }
    acc[6]='a';
  }
  
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
  
  Serial.begin(9600);

  // WI-FI
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println(WiFi.localIP());

  // MQTT Subscribe
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  client.subscribe("/temperature");
  client.subscribe("/humidity");
  client.subscribe("/acceleration");
  
}

void loop() {

  // MQTT Connection
   if (!client.connected()) {
    reconnect();
  }
  
  client.loop();

  // Response request to Arduino
   if(Serial.available() > 0){
    Serial.write(temp);
    Serial.write(hum);
    Serial.write(acc);
   }
   
  delay(4000);
}
