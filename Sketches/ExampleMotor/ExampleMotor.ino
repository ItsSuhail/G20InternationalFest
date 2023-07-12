int MotorPin = 7;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 8 as an output.
  pinMode(MotorPin, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(MotorPin, HIGH);  // turn the MOTOR on (HIGH is the voltage level)
  // delay(10000);                      // wait for 10 second
  // digitalWrite(8, LOW);   // turn the MOTOR off by making the voltage LOW
  // delay(1000);                      // wait for a second
}
