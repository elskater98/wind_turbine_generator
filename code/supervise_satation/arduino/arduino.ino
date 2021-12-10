#include "Wire.h"
#include "ESP8266.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); //RX, TX

#define I2C_ADDR 0x04

// variables
int data[2]; // temp, hum

float temp = 0.0;
float hum = 0.0;

void reciveDataHandler(){
  
}

void sendDataHandler(){
   data[0] = random(1,30);; //temp
   data[1] = random(1,30);; //hum

   for(int i=0;i<2;i++){
     Wire.write(data[i]);
   }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(115200);
  Wire.begin(I2C_ADDR);

  // Recive Data From ESP-01
  //Wire.onReceive(reciveDataHandler);

  // Send Data To Raspberry Pi
  Wire.onRequest(sendDataHandler);
  delay(100);
}

void loop() {
  temp = random(1,30);
  Serial.println(temp);
  hum = random(1,30);
  Serial.println(hum);
  delay(1000);
}
