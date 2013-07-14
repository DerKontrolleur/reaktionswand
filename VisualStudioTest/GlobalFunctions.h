#pragma once

#include <string.h>

////////////////////////////////////////////////////////////////////
////  VARIABLES ///////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// Messages
static const String STOP = "stop\n";
static const String START = "start\n";
static const String BACK = "back\n";
static const String HOME = "home\n";
static const String TICTACTOE = "tictactoe\n";
static const String REACTION_F = "reactionf\n";
static const String REACTION_T = "reactiont\n";
static const String FOURWINS = "fourwins\n";
static const String SCREENSAVER = "screen\n";
static const String PROGRAMS = "programs\n";
static const String SENSORTEST = "sensor\n";
static const String LIHGTTEST_1 = "light1\n";

// Time
static unsigned long time = 0;

// Number of LEDs
static const int LEDs = 4;

// Pins for LEDs (LPD6803)
static const int DataPin = 51;
static const int ClockPin = 53;

// Pins for sensors (74HC165)
static const int datapin = 2; //connect to pin 9 of shift register
static const int clockpin = 3; //connect to pin 2 of shift register
static const int latchpin = 4; //connect to pin 1 of shift register

// Setup sensors
Sensor sensors1 = Sensor(latchpin, datapin, clockpin);
Sensor sensors2 = Sensor(latchpin, datapin, clockpin);
Sensor sensors3 = Sensor(latchpin, datapin, clockpin);
Sensor sensors4 = Sensor(latchpin, datapin, clockpin);
Sensor sensors5 = Sensor(latchpin, datapin, clockpin);
Sensor sensors6 = Sensor(latchpin, datapin, clockpin);
Sensor sensors7 = Sensor(latchpin, datapin, clockpin);
Sensor sensors8 = Sensor(latchpin, datapin, clockpin);

// Setup lights
LPD6803 lights = LPD6803(LEDs, DataPin, ClockPin);


////////////////////////////////////////////////////////////////////
////  FUNCTIONS  //////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


// Blink a defined light
long blink_time = 0;
int blinkLEDState = LOW;
void blinkLight(long del, int light) {
  if(time - blink_time > del) {
    blink_time = time;
    if(blinkLEDState == LOW) {
      lightOn(light,0,31,0);
      blinkLEDState = HIGH;
    }
    else {
      lightOff(light);
      blinkLEDState = LOW;
    }
  }
}


// Wait for set amount of time. How to: if(wait(100) == true) do something
static long wait_time = 0;
boolean wait(long t) {
  if(wait_time == 0) {
    wait_time = time;
  }
  if(time - wait_time > t) {
    wait_time = 0;
    return true;
  }
  return false;
}


// Read data (must be called once in main loop)
static String buffer = "";
static char input = 'x';
void Read() {
  if(Serial3.available()) {
    input = (char)Serial3.read();
      
    if(input != '\0') {
      buffer += input;
    }
      
    delay(10);
  }
  
  // Trigger action if word ends
  if(input == '\n') {
    // Send confirmation
    Serial3.print(buffer);
    
    // Trigger
    if(buffer == START) {
      digitalWrite(13,HIGH);
    }
    if(buffer == STOP) {
      digitalWrite(13,LOW);
    }
    buffer = "";
    input = 'x';
  }
}


// Access lights 0 to "number of LEDs"
void lightsOn(int from, int to, int red, int green, int blue) {
  for(int LED = from; LED <= to; LED++) {
    lights.setPixelColor(LED, red, green, blue);
  }
  lights.show();
  delay(20);
}

void lightsOn(int from, int to, uint16_t color) {
  for(int LED = from; LED <= to; LED++) {
    lights.setPixelColor(LED, color);
  }
  lights.show();
  delay(20);
}


// Access specific light
void lightOn(int LED, int red, int green, int blue) {
  lights.setPixelColor(LED, red, green, blue);
  lights.show();
  delay(20);
}

void lightOn(int LED, uint16_t color) {
  lights.setPixelColor(LED, color);
  lights.show();
  delay(20);
}


void lightOff(int LED) {
  lights.setPixelColor(LED,0,0,0);
  lights.show();
  delay(20);
}

void allLightsOff(int LEDs) {
  for(int LED = 0; LED <= LEDs; LED++) {
    lights.setPixelColor(LED, 0, 0, 0);
  }
  lights.show();
  delay(20);
}
 

// Get value of one specific sensor
int getSensor(int sensor) {
  int value = 0;
  if(sensor < 8) {
    value = sensors1.check(sensor);
  }
  else if(sensor < 16) {
    value = sensors2.check(sensor);
  }
  else if(sensor < 24) {
    value = sensors3.check(sensor);
  }
  else if(sensor < 32) {
    value = sensors4.check(sensor);
  }
  else if(sensor < 40) {
    value = sensors5.check(sensor);
  }
  else if(sensor < 48) {
    value = sensors6.check(sensor);
  }
  else if(sensor < 56) {
    value = sensors7.check(sensor);
  }
  else if(sensor < 64) {
    value = sensors8.check(sensor);
  }
  return value; 
}


// Check all sensors
int getSensors(int from, int to) {
  int value = 0;
  for(int sensor = from; sensor <= to; sensor++) {
    if(sensor < 8) {
      value = sensors1.check(sensor);
    }
    else if(sensor < 16) {
      value = sensors2.check(sensor);
    }
    else if(sensor < 24) {
      value = sensors3.check(sensor);
    }
    else if(sensor < 32) {
      value = sensors4.check(sensor);
    }
    else if(sensor < 40) {
      value = sensors5.check(sensor);
    }
    else if(sensor < 48) {
      value = sensors6.check(sensor);
    }
    else if(sensor < 56) {
      value = sensors7.check(sensor);
    }
    else if(sensor < 64) {
      value = sensors8.check(sensor);
    }
  }
  return value; 
}


// Create a 15 bit color value from R,G,B
unsigned int color(byte r, byte g, byte b) {
  // Take the lowest 5 bits of each value and append them end to end
  return(((unsigned int)g & 0x1F )<<10 | ((unsigned int)b & 0x1F)<<5 | (unsigned int)r & 0x1F);
}


// Preconfigured colors
unsigned int Colors(int s) {
  int r,g,b;
  switch(s) {
    case 0:  r= 0;g=25;b=31; break;     
    case 1:  r= 0;g= 0;b=16; break;      
    case 2:  r= 5;g=31;b=19; break;      
    case 3:  r=10;g=31;b= 0; break;      
    case 4:  r=31;g= 0;b= 0; break;      
    case 5:  r= 0;g=31;b= 0; break;      
    case 6:  r= 0;g= 0;b=31; break;      
    case 7:  r=31;g=31;b= 0; break;      
    case 8:  r=31;g= 0;b=31; break;      
    case 9:  r=31;g=31;b=31; break;      
    case 10: r= 0;g= 0;b=16; break;      
    case 11: r=31;g= 5;b= 0; break;      
    case 12: r=31;g= 8;b= 0; break;      
    case 13: r=31;g= 0;b= 5; break;      
    case 14: r=28;g=18;b= 1; break;
    case 15: r=28;g=18;b= 0; break;
    case 16: r= 2;g=14;b=28; break;
  }
  return(color(r,g,b));
}