#include <SoftwareSerial.h>
#include <AFMotor.h>

// Defining the IR Sensors
const int ProxSensorL = A2;
const int ProxSensorR = A5;

// Defining timeperiod for turning
const int timePeriod = 100; // In milliseconds

int speedOfM1 = 75;
int speedOfM2 = 75;
int speedOfM3 = 100;
int speedOfM4 = 100;
// int maximumSpeed = 150;

// Creating an object and defining the four car motor at pins 1, 2, 3 and 4
AF_DCMotor backLeft(1); // M1
AF_DCMotor backRight(2); // M2
AF_DCMotor frontRight(3); // M3
AF_DCMotor frontLeft(4); // M4

void setup() {
  pinMode(ProxSensorL, INPUT);
  pinMode(ProxSensorR, INPUT);
  Serial.begin(9600);	// Define baud rate for serial communication for testing
}

void loop() {
  // Implies if car is currently on white surface
  if (
    digitalRead(ProxSensorL) == 0 &&
    digitalRead(ProxSensorR) == 0
  ) { forwardAll(); }

  // Implies if left sensor is on black surface while the right one is not
  else if (
    digitalRead(ProxSensorL) == 1 &&
    digitalRead(ProxSensorR) == 0
  ) { turnLeft(); }

  // Implies if right sensor is on black surface while the left one is not
  else if (
    digitalRead(ProxSensorL) == 0 &&
    digitalRead(ProxSensorR) == 1
  ) { turnRight(); }

  // If both the sensors are on black surface
  else { stopAll(); }
}

void turnLeft() {
  stopAll();

  frontRight.setSpeed(speedOfM3 + 50); backRight.setSpeed(speedOfM2 + 50);
  backRight.run(FORWARD); frontRight.run(FORWARD);
  frontLeft.setSpeed(speedOfM4 + 50); backLeft.setSpeed(speedOfM1 + 50);
  backLeft.run(BACKWARD); frontLeft.run(BACKWARD);

  speedReset();
}

void turnRight() {
  stopAll();

  frontLeft.setSpeed(speedOfM4 + 50); backLeft.setSpeed(speedOfM1 + 50);
  backLeft.run(FORWARD); frontLeft.run(FORWARD);
  frontRight.setSpeed(speedOfM3 + 50); backRight.setSpeed(speedOfM2 + 50);
  backRight.run(BACKWARD); frontRight.run(BACKWARD);

  speedReset();
}

void forwardAll() {
  frontRight.setSpeed(speedOfM3);
  backRight.setSpeed(speedOfM2);
  frontLeft.setSpeed(speedOfM4);
  backLeft.setSpeed(speedOfM1);

  // Setting all motors to forward direction
  frontRight.run(FORWARD);
  backRight.run(FORWARD);
  frontLeft.run(FORWARD);
  backLeft.run(FORWARD);
}

void backwardAll() {
  frontRight.setSpeed(speedOfM3);
  backRight.setSpeed(speedOfM2);
  frontLeft.setSpeed(speedOfM4);
  backLeft.setSpeed(speedOfM1);
  
  // Setting all motors to backward direction
  backRight.run(BACKWARD);
  backLeft.run(BACKWARD);
  frontRight.run(BACKWARD);
  frontLeft.run(BACKWARD);
}

void stopAll() {
  frontRight.run(RELEASE);
  frontLeft.run(RELEASE);
  backRight.run(RELEASE);
  backLeft.run(RELEASE);
}

void speedReset() {
  frontRight.setSpeed(speedOfM4);
  frontLeft.setSpeed(speedOfM3);
  backRight.setSpeed(speedOfM2);
  backLeft.setSpeed(speedOfM1);
}