void setup() {
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
}

void loop() {
  digitalWrite(6,LOW);
  for(int i=0; i<255; i++) {
    analogWrite(5,i);
    delay(10);
  }
  
  delay(1000);
  
  for(int i=255; i>0; i--) {
    analogWrite(5,i);
    delay(10);
  }
  
  digitalWrite(5,LOW);
  delay(1000);

  for(int i=0; i<255; i++) {
    analogWrite(6,i);
    delay(10);
  }
  
  delay(1000);
  
  for(int i=255; i>0; i--) {
    analogWrite(6,i);
    delay(10);
  }
  
  digitalWrite(6,LOW);
  delay(1000);
  
}
