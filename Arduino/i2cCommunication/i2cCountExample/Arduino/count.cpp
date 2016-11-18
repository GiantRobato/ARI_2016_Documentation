#include <Wire.h>

#define SLAVE_ADDRESS 0x04

void setup() {
  Serial.begin(9600);
  // begin as slave
  Wire.begin(SLAVE_ADDRESS);
  
  //On recieve handler
  Wire.onRequest(sendData);
  
  Serial.println("Ready!");
}

void loop() {
  delay(10);
}

void sendData(){
  static char c = '0';

  Wire.write(c++);
  if (c > 'z') c = '0';
}
