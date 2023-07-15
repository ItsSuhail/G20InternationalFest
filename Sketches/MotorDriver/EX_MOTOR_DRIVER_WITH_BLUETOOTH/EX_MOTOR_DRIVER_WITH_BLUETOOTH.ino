#include <SoftwareSerial.h>
#include <AFMotor.h>

// Defining a time period for turning the car
const int turningTimePeriod = 3 * 1000; // time period in milliseconds

const char B = 'B';
const char F = 'F';
const char L = 'L';
const char R = 'R';

// Creating an object and defining the four car motor at pins 1, 2, 3 and 4
AF_DCMotor frontRight(1);
AF_DCMotor frontLeft(2);
AF_DCMotor backLeft(3);
AF_DCMotor backRight(4);

/* Create object named BluetoothModule of the class SoftwareSerial */ 
SoftwareSerial BluetoothModule(0,1); /* (Rx,Tx) */	

void setup() {
  BluetoothModule.begin(9600);	/* Define baud rate for Sofware serial communication or Bluetooth Communication */
  // Serial.begin(9600);	/* Define baud rate for serial communication for testing */
}

void loop() {
  /*Checks If data is available on serial port */
  if (BluetoothModule.available()) {
    Serial.write(BluetoothModule.read()); // For printing whatever data is being sent
    if(BluetoothModule.read() == F){
      forwardAll();
    }
    else if(BluetoothModule.read() == B){
      backwardAll();
    }
    else if(BluetoothModule.read() == L){
      goLeft();
    }
    else if(BluetoothModule.read() == R){
      goRight();
    }
  }
}

void goLeft() {
  stopAll();
  frontRight.setSpeed(255);backRight.setSpeed(255);
  backRight.run(FORWARD);frontRight.run(FORWARD);
  frontLeft.setSpeed(255);backLeft.setSpeed(255);
  backLeft.run(BACKWARD);frontLeft.run(BACKWARD);
  // delay(turningTimePeriod);
  // stopAll();
}

void goRight() {
  stopAll();
  frontLeft.setSpeed(255);backLeft.setSpeed(255);
  backLeft.run(FORWARD);frontLeft.run(FORWARD);
  frontRight.setSpeed(255);backRight.setSpeed(255);
  backRight.run(BACKWARD);frontRight.run(BACKWARD);
  // delay(turningTimePeriod);
  // stopAll();
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
  frontRight.run(BRAKE);
  frontLeft.run(BRAKE);
  backRight.run(BRAKE);
  backLeft.run(BRAKE);
}
