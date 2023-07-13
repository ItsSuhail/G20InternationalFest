// Motor A connections
const int enA = 9;
const int in1 = 8;
const int in2 = 7;

// Motor B connections
const int enB = 3;
const int in3 = 5;
const int in4 = 4;

// The two directions
const char* FORE = "fore";
const char* BACK = "back";

// Motor names
const char* FL = "FL"; // Fore left
const char* FR = "FR"; // Fore right
const char* BL = "BL"; // Back left
const char* BR = "BR"; // Back right

void setup() {
	// Set all the motor control pins to outputs
	pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
	
	// Turn off motors - Initial state
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
  analogWrite(enA, 255);
  analogWrite(enB, 255);
}

void loop() {
}

// One function to change the speed and direction of the motor.
void alterMotor(const char* motor, const char* direction, int speed) {

  // If motor is the front left.
  if (strcmp(motor, FL) == 0) {
    analogWrite(enA, speed);
    if (strcmp(direction, FORE) == 0) { // Set motor to move forward
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
    } else if  (strcmp(direction, BACK) == 0) { // Set motor to move backward
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
    } else { Serial.println("Invalid direction, Must be FORE or BACK.") }
  }

  // If motor is the front right.
  else if (strcmp(motor, FR) == 0) {
    analogWrite(enB, speed);
    if (strcmp(direction, FORE) == 0) { // Set motor to move forward
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
    } else if  (strcmp(direction, BACK) == 0) { // Set motor to move backward
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
    } else { Serial.println("Invalid direction, Must be FORE or BACK.") }
  }

  // If motor is the back left.
  // If motor is the back right.

  else { Serial.println("Invalid motor, Must be of { FR, FL, BR, BL }.") }
}
