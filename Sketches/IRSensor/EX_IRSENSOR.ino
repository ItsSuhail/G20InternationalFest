// Initializing
int IRSensor = 3;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // Init Serial at 115200 Baud Rate.
  pinMode(IRSensor, INPUT); // IR Sensor pin INPUT
  pinMode(13, OUTPUT); // InBuilt LED Pin Output
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorStat = digitalRead(IRSensor);
  if(sensorStat == 1){
    digitalWrite(13, LOW);
  }
  else{
    digitalWrite(13, HIGH);
  }
}
