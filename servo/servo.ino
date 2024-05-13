#include <Servo.h>

int count = 0;
int passcode[6]={2,3,1,3,2,1}; //passcode to open safe. Blue=1, Red=2, Green=3.
int timeout = 250; //delay in between button presses.
int correct = 0; //Number of consecutive correct inputs
Servo myservo10;
Servo myservo7;

void setup() {
  digitalWrite(4, HIGH);
  Serial.begin(9600);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  myservo10.attach(10);
  myservo7.attach(2);
  myservo10.write(34);
}

void loop() {
  if (digitalRead(7)==HIGH||digitalRead(8)==HIGH||digitalRead(9)==HIGH){
    tone(11, 2000, 50);
    count+=1;
    if (digitalRead(7) == HIGH && digitalRead(8) == LOW && digitalRead(9) == LOW) {
      Serial.println("1");
      if(passcode[(count-1)]==1){
        correct+=1;
      }else{
        correct=0;
      }
    } else if(digitalRead(7) == LOW && digitalRead(8) == HIGH && digitalRead(9) == LOW){
      Serial.println("2");
      if(passcode[count-1]==2){
        correct+=1;
      }else{
        correct=0;
      }
    } else if (digitalRead(7) == LOW && digitalRead(8) == LOW && digitalRead(9) == HIGH){
      Serial.println("3");
      if(passcode[(count-1)]==3){
        correct+=1;
      }else{
        correct=0;
      }
  }
    Serial.print("Count: ");
    Serial.println(count);
    Serial.print("Correct: ");
    Serial.println(correct);
    Serial.print("Actual: ");
    Serial.println(passcode[count-1]);
    Serial.println(" ");
    delay(timeout);
}
    
  if(count == 6 && correct == 6){
    count=0;
    correct=0;
    //activate servo and change LED status to Green
    digitalWrite(4, LOW);
    myservo10.write(170);
    for(int i=0; i<90; i++) {
      if(i==5 || i==15 || i==25) {
        tone(11,3000,250);
        digitalWrite(3, HIGH);
      } else if(i==10 || i==20){
        digitalWrite(3, LOW);
      }
      myservo7.write(i);
      delay(50);
    }
    
    delay(7000);
    digitalWrite(3, LOW);
    digitalWrite(5, HIGH);
    
    for(int i=90; i>0; i--) {
      myservo7.write(i);
      delay(50);
    }
      
  } else if (count == 6 && correct != 6) {
      count = 0;
      correct = 0;
      for(int i = 0; i < 4; i++) {
        tone(11, 1800, 50);
        digitalWrite(4, HIGH);
        delay(50);
        digitalWrite(4, LOW);
        delay(50);
      }
  }
    //deactivate servo change LED status to Red
    digitalWrite(5, LOW);
    digitalWrite(4, HIGH);
    delay(150);
    myservo10.write(34);
    myservo7.write(0);
}
