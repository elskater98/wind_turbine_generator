// Import required libraries
#include <Arduino.h>
#include <ESP8266WiFi.h>

//#include <SoftwareSerial.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include <SPI.h>
#include <SparkFun_ADXL345.h>

// Replace with your network credentials
const char* ssid = "ADAMO-C6CA";
const char* password = "JA54W6HGFCV7NC";

LiquidCrystal_I2C lcd(0x27,16,2);

ADXL345 adxl = ADXL345();

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
}

void loop(){
    int x, y, z;
    adxl.readAccel(&x, &y, &z); 
    lcd.clear();
    lcd.print((String)"X:"+x+" Y:"+y+" Z:"+z);
    delay(200);
}
