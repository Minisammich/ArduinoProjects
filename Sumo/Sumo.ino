bool CW = true;
bool CCW = false;
bool mRun = true;
bool mBrake = false;

bool currDirection = CW;

bool runningState = false;

int startDelay = 5000;

void setup() {
  #define motorPin_1 5
  #define motorPin_2 6
  #define motorPin_3 10
  #define motorPin_4 9
    
  #define trigPin 11
  #define echoPin 12
  
  #define lineSensor_1 2
  #define lineSensor_2 3
  #define lineSensor_3 4

  #define buttonPin 7
  #define LED_PIN 8
  
  pinMode(lineSensor_1,INPUT);
  pinMode(lineSensor_2,INPUT);
  pinMode(lineSensor_3,INPUT);

  pinMode(motorPin_1,OUTPUT);
  pinMode(motorPin_2,OUTPUT);
  pinMode(motorPin_3,OUTPUT);
  pinMode(motorPin_4,OUTPUT);
}

void loop() {
  mvFwd(100);
  delay(1000);
  stopMotors();
  delay(1000);
}

void motorAccelTest() {
  accelMotors(CW,100,10,100);
  delay(1000);
  accelMotors(CW,100,100,0);
  m1(CW,0,0);
  m2(CW,0,0);
  delay(1000);
}

void ultrasonicSensor() { // Sequence when a robot is spotted.
  long duration;
  int distance;
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  return(distance);
}

void lineSensors() { // Sequence for line avoidance.
  if(digitalRead(lineSensor_1) == HIGH && digitalRead(lineSensor_2) == HIGH) {
    mvFwd(100);
  } else if(digitalRead(lineSensor_3 == HIGH) && digitalRead(lineSensor_1) == HIGH) {
    
  }
  
}

void buttonPressed() { // Starting button delay and LED flashing sequence.
  if(digitalRead(buttonPin) == LOW) {
    for(int i = startDelay; i > 0; i--) {
      if(i & 2 == 0) {
        digitalWrite(LED_PIN, HIGH);
      } else {
        digitalWrite(LED_PIN, LOW);
      }
      if(i == 0) {
        runningState = true;
      }
    }
  } 
  runningState = true;
}

void m1(bool direction, int speed, bool mState) {
  int pwm = map(speed,0,100,0,255); // Makes it more user friendly... 0 -> 100% maps to: 0 -> 255.
  if(mState==mRun) {
    if(direction==CW) {
      analogWrite(motorPin_1,pwm);
      analogWrite(motorPin_2,LOW);
    } else if(direction==CCW) {
      analogWrite(motorPin_1,LOW);
      analogWrite(motorPin_2,pwm);
    }
  } else if(mState==mBrake) {
    analogWrite(motorPin_1,HIGH);
    analogWrite(motorPin_2,HIGH);
  } else {
    analogWrite(motorPin_1,LOW);
    analogWrite(motorPin_2,LOW);
  }
}

void m2(bool direction, int speed, bool mState) {
  int pwm = map(speed,0,100,0,255);
  if(mState=mRun) {
    if(direction==CW) {
      analogWrite(motorPin_3,pwm);
      analogWrite(motorPin_4,LOW);
    } else if(direction==CCW) {
      analogWrite(motorPin_3,LOW);
      analogWrite(motorPin_4,pwm);
    }
  } else if(mState==mBrake) {
    analogWrite(motorPin_3,HIGH);
    analogWrite(motorPin_4,HIGH);
  } else {
    analogWrite(motorPin_3,LOW);
    analogWrite(motorPin_4,LOW);
  }
}

void mvFwd(int speed) { // Move Forwards Indefinitely.
  m1(CW, speed, mRun);
  m2(CW, speed, mRun);
}

void mvBwd(int speed) { // Move Backwards Indefinitely.
  m1(CCW, speed, mRun);
  m2(CCW, speed, mRun);
}

void tnRt(int speed) { // Turn Right Indefinitely.
  m1(CW, speed, mRun);
  m2(CW, 0, mBrake);
}

void tnLt(int speed) { // Turn Left Indefinitely.
  m1(CW, 0, mBrake);
  m2(CW, speed, mRun);
}

void stopMotors() {
  m1(CW, 0, mBrake);
  m2(CW, 0, mBrake);
}

void accelMotors(bool direction, int acceleration, int initialSpeed, int finalSpeed) {
  if(initialSpeed < finalSpeed) {
    for(int i=initialSpeed; i<finalSpeed; i+=1) {
      m1(direction,i,mRun);
      m2(!direction,i,mRun);
      delay(map(acceleration,0,100,100,0));
    } 
  } else if(initialSpeed > finalSpeed) {
      for(int i=initialSpeed; i>finalSpeed; i-=1) {
      m1(direction,i,mRun);
      m2(!direction,i,mRun);
      delay(map(acceleration,0,100,100,0));
    }
  }
}
