#include <Servo.h> 

Servo myservo;	// create servo object to control a servo
int pos = 0;	// variable to store the servo position

void setup() 
{
	// attaches the servo on pin 10 to the servo object
	myservo.attach(10);
  myservo.write(0);
}

void loop() 
{
}