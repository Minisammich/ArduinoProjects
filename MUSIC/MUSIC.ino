int potvalue = 0;
void setup() {
  Serial.begin(9600);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(11, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  if (digitalRead(7) == HIGH && digitalRead(8) == LOW && digitalRead(9) == LOW) {
    tone(11, 261.63, 100);
    digitalWrite(5, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
    delay(100);
  } else if (digitalRead(7) == LOW && digitalRead(8) == HIGH && digitalRead(9) == LOW) {
    tone(11, 293.66, 100);
    digitalWrite(5, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(3, LOW);
    delay(100);
  } else if (digitalRead(7) == LOW && digitalRead(8) == LOW && digitalRead(9) == HIGH) {
    tone(11, 329.63, 100);
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
    digitalWrite(3, HIGH);
    delay(100);
  } else if (digitalRead(7) == HIGH && digitalRead(8) == LOW && digitalRead(9) == HIGH) {
    tone(11, 349.23, 100);
    digitalWrite(5, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(3, HIGH);
    delay(100);
  } else if (digitalRead(7) == LOW && digitalRead(8) == HIGH && digitalRead(9) == HIGH) {
    tone(11, 392, 100);
    digitalWrite(5, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(3, HIGH);
    delay(100);
  } else if (digitalRead(7) == HIGH && digitalRead(8) == HIGH && digitalRead(9) == LOW) {
    tone(11, 440, 100);
    digitalWrite(5, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(3, LOW);
    delay(100);
  } else if (digitalRead(7) == HIGH && digitalRead(8) == HIGH && digitalRead(9) == HIGH) {
    tone(11, 493.88, 100);
    digitalWrite(5, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(3, HIGH);
    delay(100);
  } else {
    digitalWrite(11, LOW);
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
    
  }
}
