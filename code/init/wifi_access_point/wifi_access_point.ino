// ESP8266 - Wifi Station
// Station Mode (WIFI_STA) -> it can connect to the wifi network as any other device

#include <ESP8266Wifi.h>
#include <Ticker.h>

Ticker tickerFunction;

void clientsConnected() {
  Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
}

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

  Serial.print("Setting soft AP configuration ...");
  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed");

  Serial.print("Setting sofAP ...");
  Serial.println(WiFi.softAP("ESPsoftAP_01") ? "Ready" : "Failed");

  Serial.print("Soft-AP IP address = ");
  Serial.print(WiFi.softAPIP());

  tickerFunction.attach(3, clientsConnected); // 3 seconds
}

void loop() {
}
}
