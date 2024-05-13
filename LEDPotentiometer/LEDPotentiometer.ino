void setup() {
  pinMode(5, OUTPUT);
  pinMode(A0, INPUT);
}

void loop() {
  potVal = digitalRead(A0);
  digitalWrite(5, HIGH);
  delay(potVal);
  digitalWrite(5, LOW);
  delay(potVal);
}
