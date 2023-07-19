#include <Servo.h>

Servo servoMotor;

int deg = 0;


void setup() {
  // put your setup code here, to run once:
  servoMotor.attach(10);
  servoMotor.write(90);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Does from 0(deg) to 180(deg) "Below code"
  for(deg = 0; deg<=180; deg+=1){
    servoMotor.write(deg);
    delay(8); // DONT EVER THINK OF REMOVING THISIIIIIIIIIIIIISSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
  }

  delay(1500);
  // Does from 180(deg) to 0(deg) "Below code"
  for(deg = 180; deg>=0; deg-=1){
    servoMotor.write(deg);
    delay(8); // DONT EVER THINK OF REMOVING THISIIIIIIIIIIIIISSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
  }
}
