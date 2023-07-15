#include <SoftwareSerial.h>

/* Create object named BluetoothModule of the class SoftwareSerial */ 
SoftwareSerial BluetoothModule(0,1); /* (Rx,Tx) */	

void setup() {
  BluetoothModule.begin(9600);	/* Define baud rate for Sofware serial communication or Bluetooth Communication */
  Serial.begin(9600);	/* Define baud rate for serial communication for testing */
}

void loop() {
  /*Checks If data is available on serial port */
  if (BluetoothModule.available()) {
    Serial.write(BluetoothModule.read());
  }
}