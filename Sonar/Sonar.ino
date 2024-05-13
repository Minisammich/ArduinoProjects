const int trigPin = 7;
const int echoPin = 4;
const int lineSenPin_1 = 2; // Line Sensor One.

long duration;
int distance; //Max distance we want is around 70cm.
int sensorState;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(lineSenPin_1, INPUT);
  Serial.begin(9600);
}

void loop() {
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
  // Prints the distance on the Serial Monitor
  
  // Serial.print("Distance: ");
  // Serial.println(distance);

  // sensorState = digitalRead(lineSenPin_1);
  Serial.println(distance);
  
}
