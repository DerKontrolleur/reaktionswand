#include <TimerOne.h>
#include "LPD6803.h"


//LPD6803 (lights)
int DataPin = 51;
int ClockPin = 53;

//lights
LPD6803 lights = LPD6803(4, DataPin, ClockPin);


void setup() {
  //begin serial comunication with 9600
  Serial.begin(115200);

  // The Arduino needs to clock out the data to the pixels
  // this happens in interrupt timer 1, we can change how often
  // to call the interrupt. setting CPUmax to 100 will take nearly all all the
  // time to do the pixel updates and a nicer/faster display, 
  // especially with strands of over 100 dots.
  // (Note that the max is 'pessimistic', its probably 10% or 20% less in reality)
  
  pinMode(DataPin, OUTPUT);
  pinMode(ClockPin, OUTPUT);
  
  lights.setCPUmax(100);  // start with 50% CPU usage. up this if the strand flickers or is slow
  
  // Start up the LED counter
  lights.begin();

  // Update the lights, to start they are all 'off'
  lights.show();
  
  //seed for random number
  randomSeed(analogRead(0));
}


void loop() {
  for(int i = 0; i <= lights.numPixels(); i++) {
    for(int j = 0; j < 31; j++) {
      if(i == 0) {
        lights.setPixelColor(i,j,0,0);
        lights.show();
        delay(50);
      }
      else if(i == 1) {
        lights.setPixelColor(i-1,0,j,0);
        lights.setPixelColor(i,j,0,0);
        lights.show();
        delay(50);
      }
      else if(i == 2) {
        lights.setPixelColor(i-2,0,0,j);
        lights.setPixelColor(i-1,0,j,0);
        lights.setPixelColor(i,j,0,0);
        lights.show();
        delay(50);
      }
      else if(i == 3) {
        lights.setPixelColor(i-3,0,0,31);
        lights.setPixelColor(i-2,0,0,j);
        lights.setPixelColor(i-1,0,j,0);
        lights.setPixelColor(i,j,0,0);
        lights.show();
        delay(50);
      }
    }
  }
  
  for(int i = 0; i <= 31; i++) {
    lights.setPixelColor(2,0,0,i);
    lights.setPixelColor(3,0,i,0);
    lights.show();
    delay(50);
  }
  
  for(int i = 0; i <= 31; i++) {
    lights.setPixelColor(3,0,0,i);
    lights.show();
    delay(50);
  }
  
  for(int i = 31; i >= 0; i--) {
    lights.setPixelColor(0,0,0,i);
    lights.setPixelColor(1,0,0,i);
    lights.setPixelColor(2,0,0,i);
    lights.setPixelColor(3,0,0,i);
    lights.show();
    delay(50);
  }
}
