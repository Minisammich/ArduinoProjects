#include <Stepper.h>

const int stepsPerRev = 2048;
float period;
int stepperSpeed = 500;

Stepper myStepper = Stepper(stepsPerRev, 8, 10, 9, 11);

void setup() {
  myStepper.setSpeed(stepperSpeed);
  Serial.begin(9600);
}

void note(float hertz, float timeHeld) {
  period = floor((0.75/(hertz)*1000000));
  Serial.println(period);
  timeHeld = (timeHeld*(hertz))/750;
  
  for(int i=0; i<=timeHeld; i++){
    if(i%2==0){
      myStepper.step(1);
    } else {
      myStepper.step(-1);
    }
    delayMicroseconds(period);
  }
}

void song1(){
  int noteLength = 500;
  
  for(int i=0; i<2; i++){
    note(261.3,noteLength);
    note(293.66,noteLength);
    note(329.63,noteLength);
    note(261.3,noteLength);
  }
  for(int i=0; i<2; i++){
    note(329.63,noteLength);
    note(349.23,noteLength);
    note(392,(noteLength)*2);
  }
  for(int i=0; i<2; i++){
    note(392,noteLength/2);
    note(440,noteLength/2);
    note(392,noteLength/2);
    note(349.23,noteLength/2);
    note(329.63,noteLength);
    note(261.63,noteLength);
  }
  for(int i=0; i<2; i++){
    note(261.63,noteLength);
    note(196, noteLength);
    note(261.63,noteLength*2);
  }
}

void loop() {
  song1();
  delay(1500);
}
