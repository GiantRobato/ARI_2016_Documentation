//
//  wheelArduino.cpp
//  This is the code for the arduino controlling the MC that run the rover's wheels
//  it sends 1.5ms ON / .5ms OFF for stop, 1.7/.3 for full forward, and 1.3/.7 for full reverse
//
//  Authors:
//  penguindustin
//  rowaneb
//  elisha
//
#include <Wire.h>
#define SLAVE_ADDRESS 0x04
const int mc1 = 5; // MC1 on GREEN 
const int mc2 = 6; // MC2 on RED
const int TOTAL_FRAME = 1960;
// int mc1Interval = 500;
// int mc2Interval = 500;
double mcInterval[2] = {500, 500};
int firstInterval = 0;
int secondInterval = 0;
int m1, m2;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  // begin as a slave
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(recvEvent);
  Serial.println("ready");
  
  pinMode(mc1, OUTPUT);
  pinMode(mc2, OUTPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0; i<2; i++) {
    if((mcInterval[i] <= 505) && (mcInterval[i] >= 495))
      mcInterval[i] = 500; 
  }
  if(mcInterval[0] > mcInterval[1]) {
    firstInterval = (int)(mcInterval[0] + 0.5);
    secondInterval = (int)(mcInterval[1] + 0.5);
    m1 = mc1;
    m2 = mc2;
  } else {
    firstInterval = (int)(mcInterval[1] + 0.5);
    secondInterval = (int)(mcInterval[0] + 0.5);
    m1 = mc2;
    m2 = mc1;
  }
  
  digitalWrite(mc1, HIGH);
  digitalWrite(mc2, HIGH);
  delayMicroseconds (TOTAL_FRAME-firstInterval);
  digitalWrite(m1, LOW);
  delayMicroseconds (firstInterval-secondInterval);
  digitalWrite(m2, LOW);
  delayMicroseconds (secondInterval);
}
void recvEvent(int numRec){
  int which = Wire.read();
  int rawInput = Wire.read();
  // make sure recv data is allowed values 
  if(((which == 0)||(which == 1)||(which == 2))&&((rawInput >= 0)||(rawInput <= 255))) { 
    // extrapolate from an input of 0 to 255 to our desired intervals
    if (which == 0)
        mcInterval[0] = 550 + 200 * (127 - rawInput) / 127;
    if (which == 1) {
        mcInterval[0] = 500 + 200 * (127 - rawInput) / 127; //FOR TESTING - SHOULD BE REMOVED (once TK1 sends mc info)
        mcInterval[1] = 500 + 200 * (rawInput - 127) / 127;
        if(rawInput == 127) { //make sure that an input of 127 results in off
          mcInterval[0] = 500;
          mcInterval[1] = 500;
        }
    } else {
      mcInterval[0] = 500;
      mcInterval[0] = 500;
    }
  }
  //mcInterval[which] = 500 + 200 * (127 - rawInput) / 127;
  Serial.println("== Recieved input ==");
  Serial.print("side: ");
  Serial.print(which);
  Serial.print("\tinput: ");
  Serial.print(rawInput);
  Serial.print("\tInterval: ");
  Serial.println(mcInterval[which]);
}
