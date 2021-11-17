// Import required libraries
#include <Arduino.h>
#include <ESP8266WiFi.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>

// Replace with your network credentials
const char* ssid = "ADAMO-C6CA";
const char* password = "JA54W6HGFCV7NC";

// DHT11
#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE    DHT11     // DHT 11

DHT dht(DHTPIN, DHTTYPE);

float t = 0.0;
float h = 0.0;

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
}

void clean_screen()
{
  Serial.write(0x7C);
  Serial.write(0x00);
}
 
void loop(){
    clean_screen();
    
    // Temperature
    float newT = dht.readTemperature();
    if (isnan(newT)) {
      Serial.println("Failed to read from DHT sensor!");
    }
    else {
      t = newT;
      String outStringT = (String) t+"C ";
      Serial.print(outStringT);
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
    }

    delay(5000);
}
