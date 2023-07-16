#include <SoftwareSerial.h>
#include <AFMotor.h>

// Defining timeperiod for turning
const int timePeriod = 100; // In milliseconds

// Defining the commands i.e BACKWARD, FORWARD, LEFT and RIGHT
const int B = 'B';
const int F = 'F';
const int L = 'L';
const int R = 'R';

// Creating an object and defining the four car motor at pins 1, 2, 3 and 4
AF_DCMotor frontRight(1);
AF_DCMotor frontLeft(2);
AF_DCMotor backLeft(3);
AF_DCMotor backRight(4);

/* Create object named BluetoothModule of the class SoftwareSerial */ 
SoftwareSerial bluetoothModule(0,1); /* (Rx,Tx) */	

void setup() {
  bluetoothModule.begin(9600);	/* Define baud rate for Sofware serial communication or Bluetooth Communication */
  Serial.begin(9600);	/* Define baud rate for serial communication for testing */
}

void loop() {
  // Checks If data is available on serial port
  if (bluetoothModule.available()) {
    char command = bluetoothModule.read(); // Converting the data sent into char
    Serial.write(command); // For printing whatever data is being sent
    alterMotors(command); // Alter the four motors based on the command sent
  }
}

void alterMotors(char motorCommand) {
  switch (motorCommand) {
    case 'S': stopAll(); break;
    case 'F': forwardAll(); break;
    case 'B': backwardAll(); break;
    case 'L': turnLeft(); break;
    case 'R': turnRight(); break;
    case 'G': forwardAll(); turnLeft(); break;
    case 'H': backwardAll(); turnLeft(); break;
    case 'I': forwardAll(); turnRight(); break;
    case 'J': backwardAll(); turnRight(); break;
    default: Serial.println("Command not implemented yet."); stopAll();
  }
}

void turnLeft() {
  stopAll();

  frontRight.setSpeed(255); backRight.setSpeed(255);
  backRight.run(FORWARD); frontRight.run(FORWARD);
  frontLeft.setSpeed(255); backLeft.setSpeed(255);
  backLeft.run(BACKWARD); frontLeft.run(BACKWARD);
}

void turnRight() {
  stopAll();

  frontLeft.setSpeed(255); backLeft.setSpeed(255);
  backLeft.run(FORWARD); frontLeft.run(FORWARD);
  frontRight.setSpeed(255); backRight.setSpeed(255);
  backRight.run(BACKWARD); frontRight.run(BACKWARD);
}

void forwardAll() {
  // Setting speed to 255
  frontRight.setSpeed(255);
  backRight.setSpeed(255);
  frontLeft.setSpeed(255);
  backLeft.setSpeed(255);

  // Setting all motors to forward direction
  frontRight.run(FORWARD);
  backRight.run(FORWARD);
  frontLeft.run(FORWARD);
  backLeft.run(FORWARD);
}

void backwardAll() {
  // Setting speed to 255
  frontRight.setSpeed(255);
  backRight.setSpeed(255);
  frontLeft.setSpeed(255);
  backLeft.setSpeed(255);
  
  // Setting all motors to forward direction
  frontRight.run(BACKWARD);
  backRight.run(BACKWARD);
  frontLeft.run(BACKWARD);
  backLeft.run(BACKWARD);
}

void stopAll() {
  frontRight.run(RELEASE);
  frontLeft.run(RELEASE);
  backRight.run(RELEASE);
  backLeft.run(RELEASE);
}