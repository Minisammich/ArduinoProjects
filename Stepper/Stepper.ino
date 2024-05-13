#include <AccelStepper.h>
#include <Adafruit_NeoPixel.h>

#define neoPixel_1 3
#define ledCount 8

Adafruit_NeoPixel strip(ledCount, neoPixel_1, NEO_GRB + NEO_KHZ800);

// Motor pin definitions:
#define motorPin1  8      // IN1 on the ULN2003 driver
#define motorPin2  9      // IN2 on the ULN2003 driver
#define motorPin3  10     // IN3 on the ULN2003 driver
#define motorPin4  11     // IN4 on the ULN2003 driver

// Define the AccelStepper interface type: 4 wire motor in half step mode:
#define MotorInterfaceType 8

// Initialize with pin sequence IN1-IN3-IN2-IN4
AccelStepper stepper = AccelStepper(MotorInterfaceType, motorPin1, motorPin3, motorPin2, motorPin4);
const int stepperSpeed = 1000;

uint32_t magenta = strip.Color(255, 0, 255);
uint32_t yellow = strip.Color(255, 160, 0);
uint32_t green = strip.Color(55, 255, 5);
uint32_t red = strip.Color(255, 5, 0);
uint32_t blue = strip.Color(10, 10, 255);

void setup() {
  // Set the maximum steps per second:
  stepper.setMaxSpeed(1000);
  Serial.begin(9600);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  strip.begin();
  strip.show();
  initialColours();
}

void initialColours(){
  strip.setPixelColor(0, 50, 50, 255);
  strip.setPixelColor(1, 255, 50, 255);
  strip.setPixelColor(2, 255, 50, 50);
  strip.setPixelColor(3, 150, 50, 0);
  strip.setPixelColor(4, 255, 255, 50);
  strip.setPixelColor(5, 50, 255, 50);
  strip.setPixelColor(6, 50, 50, 255);
  strip.setPixelColor(7, 255, 255, 255);
  strip.show();
}

void loop() {
  if(digitalRead(7)==HIGH) {
    strip.clear();
    strip.show();
    while(stepper.currentPosition() > -2048){
      if(abs(stepper.currentPosition())==0||abs(stepper.currentPosition())==256||abs(stepper.currentPosition())==512||abs(stepper.currentPosition())==768||abs(stepper.currentPosition())==1024||abs(stepper.currentPosition())==1280||abs(stepper.currentPosition())==1536||abs(stepper.currentPosition())==1792){
        strip.fill(yellow, 0, ((1+abs(stepper.currentPosition())/256)));
        strip.show();
        Serial.println(abs(stepper.currentPosition())/256);
      }
      stepper.setSpeed(-stepperSpeed);
      stepper.runSpeed();
    }
  stepper.setCurrentPosition(0);
  strip.clear();
  strip.show();
  }
  if(digitalRead(6)==HIGH) {
    strip.fill(green, 0, 8);
    strip.show();
    while( stepper.currentPosition() > -284){
      stepper.setSpeed(-stepperSpeed);
      stepper.runSpeed();
    }
    stepper.setCurrentPosition(0);
  }
  if(digitalRead(5)==HIGH){
    strip.fill(red, 0, 8);
    strip.show();
    while( stepper.currentPosition() < 284) {
      stepper.setSpeed(stepperSpeed);
      stepper.runSpeed();
    }
    stepper.setCurrentPosition(0);
  }
  if(digitalRead(4)==HIGH) {
    strip.clear();
    strip.show();
    while(stepper.currentPosition() < 2048){
      if(abs(stepper.currentPosition())==0||abs(stepper.currentPosition())==256||abs(stepper.currentPosition())==512||abs(stepper.currentPosition())==768||abs(stepper.currentPosition())==1024||abs(stepper.currentPosition())==1280||abs(stepper.currentPosition())==1536||abs(stepper.currentPosition())==1792){
        strip.fill(blue, 0, ((1+abs(stepper.currentPosition())/256)));
        strip.show();
        Serial.println(abs(stepper.currentPosition())/256);
      }
      stepper.setSpeed(stepperSpeed);
      stepper.runSpeed();
    }
    strip.clear();
    strip.show();
    stepper.setCurrentPosition(0);
  }
}
