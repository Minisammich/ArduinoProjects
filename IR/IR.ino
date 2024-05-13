#include <SharpIR.h>

#define IRPin A0
#define model 1080

int distance_cm;

SharpIR mySensor(model, IRPin);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  distance_cm = mySensor.getDistance(true);

  Serial.print("distance: ");
  Serial.println(distance_cm);
}
