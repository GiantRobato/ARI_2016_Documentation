/* Name: stepperTestV1
 *
 * Description: arduino code to test Microstep Driver-ST6600 from
 * stepperonline
 *
 */

const int pulPin = 8; //pulse to move
const int dirPin = 9; //direction
const int enablePin = 3;

void setup() {
  pinMode(pulPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  
  digitalWrite(pulPin,LOW);
  digitalWrite(dirPin,LOW);
  digitalWrite(enablePin,HIGH);
  
  for(int i = 0; i < 50000; i++){
    digitalWrite(pulPin,HIGH);
    delayMicroseconds(50);
    digitalWrite(pulPin,LOW);
    delayMicroseconds(50);
  }
}

void loop() {
}