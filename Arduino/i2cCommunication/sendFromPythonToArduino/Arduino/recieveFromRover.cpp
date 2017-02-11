#include <Wire.h>

#define SLAVE_ADDRESS 0x04

void setup() {
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(recvData);
  Serial.println("Ready!");
}

void loop() {
  delay(10);
}

//How many refers to the number of bytes read from
//the master
void recvData(int howMany){
  int x = Wire.read();
  Serial.println(x);
}
