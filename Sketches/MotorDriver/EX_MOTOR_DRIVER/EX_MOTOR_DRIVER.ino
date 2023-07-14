#include <AFMotor.h>

// Creating an object and defining frontLeft motor at "pin 1" or simply numbered "1"
AF_DCMotor frontLeft(1);

void setup() 
{
  // Sets the speed of the motor to 200 (ranges from 0-255)
	frontLeft.setSpeed(200);
	frontLeft.run(FORWARD); // Runs the left front motor forward
}

void loop() 
{
}