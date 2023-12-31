#include <AFMotor.h>

// Defining a time period for turning the car
// time period in milliseconds
const int turningTimePeriod = 3 * 1000; 

// Creating an object and defining the four car motor at pins 1, 2, 3 and 4
AF_DCMotor frontRight(1);
AF_DCMotor frontLeft(2);
AF_DCMotor bottomLeft(3);
AF_DCMotor bottomRight(4);

void setup() 
{
  // Sets the speed of the motor to 200 (ranges from 0-255)
	frontRight.setSpeed(255);
	frontRight.run(FORWARD); // Runs the Right front motor forward
  delay(5000);
  goLeft();
  delay(10000);
}


// Not fully implemented as we need to see how much duration is required
void goLeft(){
  stopAll();
  frontRight.setSpeed(255);bottomRight.setSpeed(255);
  bottomRight.run(FORWARD);frontRight.run(FORWARD);
  frontLeft.setSpeed(255);bottomLeft.setSpeed(255);
  bottomLeft.run(FORWARD);frontLeft.run(FORWARD);
  delay(turningTimePeriod);
  stopAll();
}

// Not fully implemented as we need to see how much duration is required
void goRight(){
  stopAll();
  frontLeft.setSpeed(255);bottomLeft.setSpeed(255);
  bottomLeft.run(FORWARD);frontLeft.run(FORWARD);
  frontRight.setSpeed(255);bottomRight.setSpeed(255);
  bottomRight.run(BACKWARD);bottomRight.run(BACKWARD);
  delay(turningTimePeriod);
  stopAll();
}


void stopAll(){
  frontRight.run(BRAKE);
  frontLeft.run(BRAKE);
  bottomRight.run(BRAKE);
  bottomLeft.run(BRAKE);
}

void loop() {

}