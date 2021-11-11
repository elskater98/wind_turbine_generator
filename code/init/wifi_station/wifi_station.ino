// ESP8266 - Wifi Station
// Station Mode (WIFI_STA) -> it can connect to the wifi network as any other device

#include <ESP8266WiFi.h>

// connection parameters
const char* ssid = "asdf";
const char* password = "asdf";

// network parameters
IPAddress staticIP(192, 168, 1, 22);
IPAddress gateway(192, 168, 1, 9);
IPAddress subnet(255, 255, 255, 0);

void setup(void) {
  
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to %s\n", ssid);

  // wifi connection configuration
  WiFi.config(staticIP, gateway, subnet);
  WiFi.begin(ssid, password);

  // checking if connected or not
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // connected
  Serial.println();
  Serial.print("Connected, IP address");
  Serial.println(WiFi.localIP());
}
