#include "Wire.h"

#define I2C_ADDR 0x04

// variables
uint8_t data[2]; // temp, hum

float temp = 0.0;
float hum = 0.0;

void reciveDataHandler(){
  
}

void sendDataHandler(){
   data[0]=temp; //temp
   data[1]=hum; //hum

   for(int i=0;i<2;i++){
     Wire.write((uint8_t)data[i]);
   }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(I2C_ADDR);

  // Recive Data From ESP-01
  //Wire.onReceive(reciveDataHandler);

  // Send Data To Raspberry Pi
  Wire.onRequest(sendDataHandler);
}

void loop() {
  temp = random(1,30);
  Serial.println(temp);
  hum = random(1,30);
  Serial.println(hum);
  delay(500);
  // put your main code here, to run repeatedly:
  
}
