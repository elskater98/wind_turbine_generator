// variables
#include "Wire.h"

#define I2C_ADDR 0x04

String msg;

void handleSendData(){
  Serial.println("Data send it");
  Wire.write((uint8_t)8);
}

void handleReceiveData(){
  while(Wire.available()> 0){
     uint8_t t = Wire.read();
    Serial.print("msg:");
    Serial.println(t);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Start");
  
  Wire.begin(I2C_ADDR);
  
  Wire.onReceive(handleReceiveData);
  Wire.onRequest(handleSendData);
  
  delay(100);
}

void loop() {

  // Request Data To ESP-01
  //Serial.write("Request Data");
  
  // Recive Data From ESP-01
  if(Serial.available() > 0){
    msg = Serial.readString();
    Serial.println(msg);
  }
  
  delay(5000);
}
