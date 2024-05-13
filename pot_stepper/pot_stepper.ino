#include <AccelStepper.h>

// Motor pin definitions:
#define motorPin1  8      // IN1 on the ULN2003 driver
#define motorPin2  9      // IN2 on the ULN2003 driver
#define motorPin3  10     // IN3 on the ULN2003 driver
#define motorPin4  11     // IN4 on the ULN2003 driver

// Define the AccelStepper interface type: 4 wire motor in half step mode:
#define MotorInterfaceType 8

// Initialize with pin sequence IN1-IN3-IN2-IN4
AccelStepper stepper = AccelStepper(MotorInterfaceType, motorPin1, motorPin3, motorPin2, motorPin4);
int stepperSpeed = 1000;

int pot1Val=0;
int pot2Val=0;

void setup() {
  // Set the maximum steps per second:
  stepper.setMaxSpeed(2000);
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}

void stepperNote(int note) {
  for(int i=0; i<=800; i++){
    if(i%2==0){
      stepper.setSpeed(stepperSpeed);
    } else { 
      stepper.setSpeed(-stepperSpeed);
    }
    stepper.run();
    delayMicroseconds(note);
  }
}


void loop() {
  stepperNote(600);
  stepperNote(500);
}
