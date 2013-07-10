#include <SensorNew.h>

int datapin = 2; //connect to pin 9 of shift register
int clockpin = 3; //connect to pin 2 of shift register
int latchpin = 4; //connect to pin 1 of shift register

int sensor = 0;

Sensor sensors = Sensor(latchpin, datapin, clockpin);

void setup() {
  
  //begin serial comunication with 115200
    Serial.begin(9600);
    
     sensors.set(latchpin, datapin, clockpin);
}

void loop() { 
  for(int i = 0; i < 4; i++) {
    if(sensors.check(i) == i) {
      Serial.println(i);
    }
  }
  delay(20);
}
    
  
