const int TRIGGER_PIN = A0;
const int ECHO_PIN = A5;
const int inter_time = 1000;

void setup() {
  Serial.begin(9600);
  pinMode (TRIGGER_PIN, OUTPUT);
  pinMode (ECHO_PIN, INPUT);
}

void loop() {
  unsigned long duration;
  float distance;
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(1000);
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn (ECHO_PIN, HIGH);
  distance = (duration / 2.0) / 29.0;
  Serial.print("Data:");
  Serial.print (millis() / 1000.0);
  Serial.print(", d = ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(inter_time);
}