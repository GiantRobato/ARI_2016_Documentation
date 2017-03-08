/* Name: BasicSteppingAMIS30543
 *
 * Description: arduino code to the AMIS 40543 stepper motor
 * controller from Pololu. This code is derived from their
 * provided example code.
 *
 * Authors: penguindustin
 *
 *  http://pololu.github.io/amis-30543-arduino/
 */

#include <SPI.h>
#include <AMIS30543.h>

const uint8_t amisDirPin = 2;
const uint8_t amisStepPin = 3;
const uint8_t amisSlaveSelect = 4;

AMIS30543 stepper;

void setup(){
  SPI.begin();
  stepper.init(amisSlaveSelect);

  // Drive the NXT/STEP and DIR pins low initially.
  digitalWrite(amisStepPin, LOW);
  pinMode(amisStepPin, OUTPUT);
  digitalWrite(amisDirPin, LOW);
  pinMode(amisDirPin, OUTPUT);

  delay(1);                  // Give the driver some time to power up.
  stepper.resetSettings();   // Reset the driver to its default settings.

  // Set the current limit.  You should change the number here to
  // an appropriate value for your particular system.
  stepper.setCurrentMilliamps(1800);
  
  stepper.setStepMode(1);   // Set the number of microsteps that correspond to one full step.
  stepper.enableDriver();   // Enable the motor outputs.
}

void loop(){
  // Step in the default direction 1000 times.
  setDirection(0);
  for (unsigned int x = 0; x < 1000; x++){
    step();
  }
  
  delay(300);   // Wait for 300 ms.

  // Step in the other direction 1000 times.
  setDirection(1);
  for (unsigned int x = 0; x < 1000; x++){
    step();
  }
  
  delay(300);   // Wait for 300 ms.
}

// Sends a pulse on the NXT/STEP pin to tell the driver to take
// one step, and also delays to control the speed of the motor.
void step(){
  // The NXT/STEP minimum high pulse width is 2 microseconds.
  digitalWrite(amisStepPin, HIGH);
  delayMicroseconds(3);
  digitalWrite(amisStepPin, LOW);
  delayMicroseconds(3);

  // The delay here controls the stepper motor's speed.  You can
  // increase the delay to make the stepper motor go slower.  If
  // you decrease the delay, the stepper motor will go fast, but
  // there is a limit to how fast it can go before it starts
  // missing steps.
  delayMicroseconds(2000);
}

// Writes a high or low value to the direction pin to specify
// what direction to turn the motor.
void setDirection(bool dir){
  // The NXT/STEP pin must not change for at least 0.5
  // microseconds before and after changing the DIR pin.
  delayMicroseconds(1);
  digitalWrite(amisDirPin, dir);
  delayMicroseconds(1);
}