////////////////////////////////////////////////////////////////////
////  VARIABLES  //////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

boolean rt_start = false;
int rt_light = 0;
int rt_prevlight = 0;
int rt_counter = 0;
const unsigned long rt_runtime = 3600000; // Time in milliseconds
unsigned long rt_starttime = 0;
unsigned long rt_updatetime = 0;


////////////////////////////////////////////////////////////////////
////  GAME  ///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

void ReactionT() {
  // Start game by touching light 0
  if(getSensor(0) != 0 && !rt_start) {   
    // Blink light 0 with 1 sec delay */
    if(wait(1000))
      lightOn(0,Colors(5));
    if(wait(1000))
      lightOff(0);  
  }
  
  // Turn light 0 off and turn random light on
  else if(getSensor(0) == 0 && !rt_start) {
    lightOff(0);
      
    // Save ID of ligt to be turned on
    rt_light = random(LEDs);
    rt_prevlight = rf_light;
      
    // One random light with random color
    lightOn(rt_light,Colors(random(16)));
        
    rt_start = true;
    
    // Save start time of game
    rt_starttime = time;
  }
  
  if(rt_start) {
    // Update time
    rt_updatetime = time;
    
    // New field and color
    if(rt_light == getSensor(rt_light)) {    
      lightOff(rt_light);
        
      rt_light = random(LEDs);
        
      // Never get same light twice
      while(rt_light == rt_prevlight) {
        rt_light = random(LEDs);
      }
        
      // Save last light
      rt_prevlight = rt_light;
          
      lightOn(rt_light,Colors(random(16)));
          
      // Count fields
      rt_counter++;
    }
    
    // Stop game   
    if((rt_updatetime - rt_starttime) >= rt_runtime) {
      allLightsOff(LEDs);
        
      // Reset everything
      rt_start = false;
      rt_counter = 0;
      rt_light = 0;
      rt_prevlight = 0;
      rt_starttime = 0;
      rt_updatetime = 0;
      
      // Send score to tablet
      Serial3.print(rt_counter);
    }
  }
}
