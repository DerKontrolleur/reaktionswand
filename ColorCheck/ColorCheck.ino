#include <TimerOne.h>
#include <LPD6803.h>
#include <Sensor.h>

//LPD6803 (lights)
int DataPin = 51;
int ClockPin = 53;

int r = 31;
int g = 3;
int b = 10;


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
  
  lights.setCPUmax(80);  // start with 50% CPU usage. up this if the strand flickers or is slow
  
  // Start up the LED counter
  lights.begin();

  // Update the lights, to start they are all 'off'
  lights.show();
}

void loop() {
     /*lights.setPixelColor(0,r,g,b);
     lights.setPixelColor(1,r,g,b);
     lights.setPixelColor(2,r,g,b);
     lights.setPixelColor(3,r,g,b);
     lights.show();
     delay(50);*/
     
     lights.setPixelColor(0,255,255,255);
     lights.setPixelColor(1,255,255,255);
     lights.setPixelColor(2,255,255,255);
     lights.setPixelColor(3,255,255,255);
     lights.show();
     delay(50);
}

// Slightly different, this one makes the rainbow wheel equally distributed 
// along the chain
void rainbowCycle(uint8_t wait) {
  int i, j;
  
  for (j=0; j < 96 * 5; j++) {     // 5 cycles of all 96 colors in the wheel
    for (i=0; i < lights.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 96-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 96 is to make the wheel cycle around
      lights.setPixelColor(i, Wheel( ((i * 96 / lights.numPixels()) + j) % 96) );
    }  
    lights.show();   // write all the pixels out
    delay(wait);
  }
}

// Create a 15 bit color value from R,G,B
unsigned int Color(byte r, byte g, byte b)
{
  //Take the lowest 5 bits of each value and append them end to end
  return( ((unsigned int)g & 0x1F )<<10 | ((unsigned int)b & 0x1F)<<5 | (unsigned int)r & 0x1F);
}

// Slightly different, this one makes the rainbow wheel equally distributed 
// along the chain
void rainbow(uint8_t wait) {
  int i, j;
   
  for (j=0; j < 96 * 5; j++) {     // 3 cycles of all 96 colors in the wheel
    for (i=0; i < lights.numPixels(); i++) {
      lights.setPixelColor(i, Wheel( (i + j) % 96));
    }  
    lights.show();   // write all the pixels out
    delay(wait);
  }
}

unsigned int Wheel(byte WheelPos)
{
  byte r,g,b;
  switch(WheelPos >> 5)
  {
    case 0:
      r=31- WheelPos % 32;   //Red down
      g=WheelPos % 32;      // Green up
      b=0;                  //blue off
      break; 
    case 1:
      g=31- WheelPos % 32;  //green down
      b=WheelPos % 32;      //blue up
      r=0;                  //red off
      break; 
    case 2:
      b=31- WheelPos % 32;  //blue down 
      r=WheelPos % 32;      //red up
      g=0;                  //green off
      break; 
  }
  return(Color(r,g,b));
}

//preconfigured colors
unsigned int colors(int s) {
  byte r,g,b;
  switch(s) {
    case 0:  r=0  ;g=155;b= 16; break;      //Siemens
    case 1:  r=0  ;b=0  ;b=128; break;      //Navy Blue
    case 2:  r=124;g=252;b=  0; break;      //Lawn Green
    case 3:  r=255;b=255;g=  0; break;      //Yellow
    case 4:  r=178;b= 34;g= 34; break;      //Firebrick
    case 5:  r=255;b= 69;g=  0; break;      //OrangeRed
    case 6:  r=199;b= 21;g=133; break;      //Medium Violet Red
    case 7:  r= 79;b=148;g=205; break;      //Deep Sky Blue
    case 8:  r=  0;b=255;g=  0; break;      //Green
    case 9:  r=255;b= 20;g=147; break;      //Deep Pink
    case 10: r=238;b=  0;g=  0; break;      //Red
    case 11: r=255;b=255;g=255; break;      //White
    case 12: r=  0;b=255;g=255; break;      //Cyan
    case 13: r=255;b=215;g=  0; break;      //Gold
    case 14: r= 34;b=139;g= 34; break;      //ForestGreen
    case 15: r= 47;b= 79;g= 79; break;      //DarkSlateGrey
    case 16: r=148;b=  0;g=211; break;      //DarkViolet 
  }
  return(Color(r,g,b));
}

