const int ProxSensor = A5;
int inputVal = 0;

void setup() 
{                
  pinMode(13, OUTPUT);          // Pin 13 has an LED connected on most Arduino boards:  
  pinMode(ProxSensor,INPUT);    //Pin 2 is connected to the output of proximity sensor
  Serial.begin(9600);
}

void loop() 
{
  digitalWrite(13, digitalRead(ProxSensor));
  int analogIROutput = analogRead(ProxSensor);
  Serial.println(digitalRead(ProxSensor));
  delay(200);              // wait for a second
}
