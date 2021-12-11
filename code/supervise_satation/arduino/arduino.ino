// variables
String msg;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Start");
  delay(100);
}

void loop() {

  // Request Data To ESP-01
  Serial.write("Request Data");
  
  // Recive Data From ESP-01
  if(Serial.available() > 0){
    msg = Serial.readString();
    Serial.println(msg);
  }
  
  delay(5000);
}
