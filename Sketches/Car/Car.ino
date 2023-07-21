#include <SoftwareSerial.h>
#include <AFMotor.h>
#include <time.h>
#include <Servo.h>

unsigned long ultrasonicDistance;

long distanceThreshold = 15;

const int TriggerPin = A2;
const int EchoPin = A3;

// Defining the IR Sensors
const int ProxSensorL = A0;
const int ProxSensorR = A5;

// Defining timeperiod for turning
const int timePeriod = 25; // In milliseconds

int speedOfCar = 100;
int maximumSpeed = 150;

// Defining the commands i.e BACKWARD, FORWARD, LEFT and RIGHT
const int B = 'B';
const int F = 'F';
const int L = 'L';
const int R = 'R';

// Defining a boolean for IR Sensors (when pressed 'delta')
boolean sensorToggle = false;

// Timer to check for bluetooth connection.
unsigned long lastBTPing;

// Creating an object and defining the four car motor at pins 1, 2, 3 and 4
AF_DCMotor backLeft(1); // M1
AF_DCMotor backRight(2); // M2
AF_DCMotor frontRight(3); // M3
AF_DCMotor frontLeft(4); // M4

// Defining servo motor
// Servo sonicServo;

/* Create object named BluetoothModule of the class SoftwareSerial */ 
SoftwareSerial bluetoothModule(0,1); /* (Rx,Tx) */	

void setup() {
    pinMode(ProxSensorL, INPUT);
    pinMode(ProxSensorR, INPUT);
    pinMode(TriggerPin, OUTPUT);
    pinMode(EchoPin, INPUT);

    // sonicServo.attach(10);
    // sonicServo.write(90);

    bluetoothModule.begin(9600);	/* Define baud rate for Sofware serial communication or Bluetooth Communication */
    Serial.begin(9600);	/* Define baud rate for serial communication for testing */
}

void loop() {
    if (bluetoothModule.available()) { // Confirm BT connection
        
        lastBTPing = millis();
        char command = bluetoothModule.read();
        // Serial.write(command); // For printing whatever data is being sent
        // If pressed on 'delta'
        if (sensorToggle == true) {
            startLaneFollowing(ProxSensorL, ProxSensorR);
        }

        alterMotors(command);
    }
    else if (millis() - lastBTPing >= 500) { // Waiting for 500ms to confirm BT Disconnection
        // Serial.println("BT Disconnected.");
        sensorToggle = false;
        stopAll();
        speedOfCar = 100;
        // sonicServo.write(90);
    }
}

void alterMotors(char motorCommand) {
  switch (motorCommand) {
    case 'S': if (!sensorToggle) { stopAll(); } break;
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
    case 'X': sensorToggle = true; break;
    case 'x': sensorToggle = false; break;
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

    if (sensorToggle) {
        frontRight.setSpeed(110); backRight.setSpeed(90);
        backRight.run(FORWARD); frontRight.run(FORWARD);
        frontLeft.setSpeed(110); backLeft.setSpeed(90);
        backLeft.run(BACKWARD); frontLeft.run(BACKWARD);
    }
    else {
        frontRight.setSpeed(speedOfCar); backRight.setSpeed(speedOfCar);
        backRight.run(FORWARD); frontRight.run(FORWARD);
        frontLeft.setSpeed(speedOfCar); backLeft.setSpeed(speedOfCar);
        backLeft.run(BACKWARD); frontLeft.run(BACKWARD);
    }
}


void turnRight() {
  
  stopAll();
  
  if (sensorToggle) {
      frontLeft.setSpeed(110); backLeft.setSpeed(90);
      backLeft.run(FORWARD); frontLeft.run(FORWARD);
      frontRight.setSpeed(110); backRight.setSpeed(90);
      backRight.run(BACKWARD); frontRight.run(BACKWARD);
  }
  else {
      frontLeft.setSpeed(speedOfCar); backLeft.setSpeed(speedOfCar);
      backLeft.run(FORWARD); frontLeft.run(FORWARD);
      frontRight.setSpeed(speedOfCar); backRight.setSpeed(speedOfCar);
      backRight.run(BACKWARD); frontRight.run(BACKWARD);
  }
}

void forwardAll() {
    // if(checkDistance() >= distanceThreshold){
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
    // }
    // else{
    //     stopAll();
    // }
    
}

void backwardAll() {
    // Setting speed to "speedOfCar"
    frontRight.setSpeed(speedOfCar);
    backRight.setSpeed(speedOfCar);
    frontLeft.setSpeed(speedOfCar);
    backLeft.setSpeed(speedOfCar);
    
    // Setting all motors to backward direction
    backRight.run(BACKWARD);
    backLeft.run(BACKWARD);
    frontRight.run(BACKWARD);
    frontLeft.run(BACKWARD);

}

void stopAll() {
  frontRight.setSpeed(0);
  frontLeft.setSpeed(0);
  backLeft.setSpeed(0);
  backRight.setSpeed(0);

  frontRight.run(FORWARD);
  frontLeft.run(FORWARD);
  backRight.run(FORWARD);
  backLeft.run(FORWARD);
}

void startLaneFollowing(int leftSensor, int rightSensor){
    // Implies if car is currently on white surface
    if (
        digitalRead(leftSensor) == 0 &&
        digitalRead(rightSensor) == 0
    ) { forwardAll(); }

    // Implies if left sensor is on black surface while the right one is not
    else if (
        digitalRead(leftSensor) == 1 &&
        digitalRead(rightSensor) == 0
    ) { turnLeft(); delay(timePeriod); }

    // Implies if right sensor is on black surface while the left one is not
    else if (
        digitalRead(leftSensor) == 0 &&
        digitalRead(rightSensor) == 1
    ) { turnRight(); delay(timePeriod); }

    // If both the sensors are on black surface
    else { stopAll(); }
}

// long checkDistance(){
//     digitalWrite(TriggerPin, HIGH);
//     delayMicroseconds(10);
//     digitalWrite(TriggerPin, LOW);
//     long duration = pulseIn(EchoPin, HIGH);

//     Serial.println((duration / 2.0) / 29.0);
//     return (duration / 2.0) / 29.0;
// }