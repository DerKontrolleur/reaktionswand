void setup()
{
  // Begin serial communication with Bluetooth
  Serial3.begin(115200);
  
  // Begin serial communication with Serial Monitor
  Serial.begin(9600);
  
  // Pins for LEDs
  pinMode(DataPin, OUTPUT);
  pinMode(ClockPin, OUTPUT);
  
  // LED on Arduino board
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
  // Test LED
  pinMode(52, OUTPUT);
  digitalWrite(52, LOW);
  
  // Number of interrupts
  lights.setCPUmax(80);
 
  // Start up the LED counter
  lights.begin();

  // Update the lights, to start they are all 'off'
  lights.show();
  
  // Seed for random number
  randomSeed(analogRead(0));
}

void loop()
{

  /* add main program code here */

}
