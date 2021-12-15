#include <SoftwareSerial.h>

#define rxPin 2 // receive
#define txPin 3 // transmit

SoftwareSerial lcdSerial =  SoftwareSerial(rxPin, txPin);
String msg;
String temp[10];
String hum[10];
String acc[10];

void clean_screen()
{
  lcdSerial.write((byte)0x7C);
  lcdSerial.write((byte)0x00);
}
void coordenades(int x, int y)
{                                  
  lcdSerial.write((byte)0x7C);         
  lcdSerial.write((byte)0x18);
  lcdSerial.write((byte)x);
  lcdSerial.write((byte)0x7C); 
  lcdSerial.write((byte)0x19);
  lcdSerial.write((byte)y);
  delay(20);
}

void pixel (int x, int y, int on_off)    
{  
  lcdSerial.write((byte)0x7C);               
  lcdSerial.write((byte)0x10);              
  lcdSerial.write((byte)x);                  
  lcdSerial.write((byte)y);
  lcdSerial.write((byte)on_off);
}

void line (int des_de_x, int des_de_y, int fins_a_x, int fins_a_y, int on_off) 
{   
  if (des_de_x<fins_a_x)
  {
    lcdSerial.write((byte)0x7C);               
    lcdSerial.write((byte)0x0C);
    lcdSerial.write((byte)des_de_x); // Primer punt
    lcdSerial.write((byte)des_de_y); 
    lcdSerial.write((byte)fins_a_x); // Segon punt
    lcdSerial.write((byte)fins_a_y);
    lcdSerial.write((byte)on_off);      
  }
  else
  {
    lcdSerial.write((byte)0x7C);               
    lcdSerial.write((byte)0x0C); 
    lcdSerial.write((byte)fins_a_x); // Segon punt
    lcdSerial.write((byte)fins_a_y);
    lcdSerial.write((byte)des_de_x); // Primer punt
    lcdSerial.write((byte)des_de_y); 
    lcdSerial.write((byte)on_off); 
  }  
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcdSerial.begin(115200);
  
  // define pin modes for tx, rx, led pins:
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  Serial.println("Start");
  lcdSerial.print("Start");
  delay(1000);
}

void loop() {
  clean_screen();
  // Request Data To ESP-01
  Serial.write("[Req]");
  Serial.println("");
  
  // Recive Data From ESP-01
  if(Serial.available() > 0){
    Serial.write("[Res]: ");
    msg = Serial.readString();
    Serial.println(msg);
    Serial.println(";");
    }
  lcdSerial.print(msg); 
  delay(5000);
}
