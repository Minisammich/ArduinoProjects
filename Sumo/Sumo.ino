bool CW = true;
bool CCW = false;
bool mRun = true;
bool mBrake = false;

bool currDirection = CW;

bool runningState = false;
bool onLine = false;

int counter = 0;
int distanceFrom;
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

  pinMode(buttonPin,OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(A0, INPUT);
  
  pinMode(lineSensor_1,INPUT);
  pinMode(lineSensor_2,INPUT);
  pinMode(lineSensor_3,INPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(motorPin_1,OUTPUT);
  pinMode(motorPin_2,OUTPUT);
  pinMode(motorPin_3,OUTPUT);
  pinMode(motorPin_4,OUTPUT);

  Serial.begin(9600);

  digitalWrite(buttonPin, HIGH);
}

void loop() {
  if(runningState == false) {
    buttonPressed();
  } else {
    lineSensors(25,250);
    if(onLine == false) {
      ultrasonicSensor();
      if(distanceFrom <= 30) {
        mvFwd(75);
        delay(150);
        counter = 0;
      } else {
        if(counter < 150) {
          mvFwd(20);
        } else if(counter < 160) {
          tnLt(30);
        } else {
          counter = 0;
        }
      }
    }
    counter++;
  }
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
  distanceFrom = distance;
}

void lineSensors(int speed, int ms) { // Sequence for line avoidance.
  if(digitalRead(lineSensor_1) == HIGH && digitalRead(lineSensor_2) == HIGH) { // Front Two.
    onLine = true;
    mvBwd(100);
    delay(ms*2);
    bwLt(100);
    delay(ms/2);
  } else if(digitalRead(lineSensor_3) == HIGH && digitalRead(lineSensor_1) == HIGH) { // Front Left and Back.
    onLine = true;
    tnRt(speed);
    delay(ms);
  } else if(digitalRead(lineSensor_3) == HIGH && digitalRead(lineSensor_2) == HIGH) { // Front Right and Back.
    onLine = true;
    tnLt(speed);
    delay(ms);
  } else if(digitalRead(lineSensor_3) == HIGH) { // Just Back.
    onLine = true;
    mvFwd(100);
    delay(ms);
  } else if(digitalRead(lineSensor_1) == HIGH) { // Just Left.
    onLine = true;
    tnShRt(speed);
    delay(ms);
  } else if(digitalRead(lineSensor_2) == HIGH) { // Just Right.
    onLine = true;
    tnShLt(speed);
    delay(ms);
  } else { // No Line Detected.
    onLine = false;
  }
  
}

void buttonPressed() { // Starting button delay and LED flashing sequence.
  if(digitalRead(A0) == HIGH) {
    for(int i = 0; i < 5; i++){
      digitalWrite(LED_PIN, HIGH);
      delay(500);
      digitalWrite(LED_PIN, LOW);
      delay(500);
    }
    runningState = true;
  }
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

void tnShRt(int speed) { // Turn Sharply Right Indefinitely.
  m1(CW, speed, mRun);
  m2(CCW, speed, mRun);
}

void tnLt(int speed) { // Turn Left Indefinitely.
  m1(CW, 0, mBrake);
  m2(CW, speed, mRun);
}

void tnShLt(int speed) { // Turn Sharply Right Indefinitely.
  m1(CCW, speed, mRun);
  m2(CW, speed, mRun);
}

void bwLt(int speed) {
  m1(CW, 0, mBrake);
  m2(CCW, speed, mRun);
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
