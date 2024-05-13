int potvalue = 0;
void setup() {
  Serial.begin(9600);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
}

void loop() {
  if (digitalRead(7) == HIGH && digitalRead(8) == LOW && digitalRead(9) == LOW) {
    tone(11, 261.63, 100);
    delay(99);
  } else if (digitalRead(8) == HIGH && digitalRead(9) == LOW) {
    tone(11, 293.66, 100);
    delay(99);
  } else if (digitalRead(9) == HIGH) {
    tone(11, 329.63, 100);
    delay(99);
  }
}
