#include <SoftwareSerial.h>
#include <AFMotor.h>
#include <time.h>

// Defining timeperiod for turning
const int timePeriod = 100; // In milliseconds

int speedOfCar = 125;
int maximumSpeed = 150;

// Defining the commands i.e BACKWARD, FORWARD, LEFT and RIGHT
const int B = 'B';
const int F = 'F';
const int L = 'L';
const int R = 'R';

// Timer to check for bluetooth connection.
unsigned long lastBTPing;

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
  if (bluetoothModule.available()) { // Confirm BT connection
    lastBTPing = millis();
    char command = bluetoothModule.read();
    // Serial.write(command); // For printing whatever data is being sent
    alterMotors(command);
  }
  else if (millis() - lastBTPing >= 500) { // Waiting for 500ms to confirm BT Disconnection
    Serial.println("BT Disconnected.");
    stopAll();
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
    case 'q': speedOfCar = maximumSpeed; break;
    case 'U': break;
    case 'u': break;
    case 'V': break;
    case 'v': break;
    case 'W': break;
    case 'w': break;
    case 'X': break;
    case 'x': break;
    // case 'J': backwardAll(); turnRight(); break;
    // case 'J': backwardAll(); turnRight(); break;
    default: setSpeedOfCar(motorCommand); break;
  }
}

void setSpeedOfCar(char speedCommand){
  int intSpeedOfCar = speedCommand - '0';
  int speed = map(intSpeedOfCar, 0, 9, 0, maximumSpeed);
  speedOfCar = speed;
}

void turnLeft() {
  stopAll();

  frontRight.setSpeed(speedOfCar); backRight.setSpeed(speedOfCar);
  backRight.run(FORWARD); frontRight.run(FORWARD);
  frontLeft.setSpeed(speedOfCar); backLeft.setSpeed(speedOfCar);
  backLeft.run(BACKWARD); frontLeft.run(BACKWARD);
}

void turnRight() {
  stopAll();

  frontLeft.setSpeed(speedOfCar); backLeft.setSpeed(speedOfCar);
  backLeft.run(FORWARD); frontLeft.run(FORWARD);
  frontRight.setSpeed(speedOfCar); backRight.setSpeed(speedOfCar);
  backRight.run(BACKWARD); frontRight.run(BACKWARD);
}

void forwardAll() {
  // Setting speed to "speedOfCar"
  frontRight.setSpeed(speedOfCar);
  backRight.setSpeed(speedOfCar);
  frontLeft.setSpeed(speedOfCar);
  backLeft.setSpeed(speedOfCar);

  // Setting all motors to forward direction
  frontRight.run(FORWARD);
  backRight.run(FORWARD);
  frontLeft.run(FORWARD);
  backLeft.run(FORWARD);
}

void backwardAll() {
  // Setting speed to "speedOfCar"
  frontRight.setSpeed(speedOfCar);
  backRight.setSpeed(speedOfCar);
  frontLeft.setSpeed(speedOfCar);
  backLeft.setSpeed(speedOfCar);
  
  // Setting all motors to forward direction
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