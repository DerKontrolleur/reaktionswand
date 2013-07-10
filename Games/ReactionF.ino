////////////////////////////////////////////////////////////////////
////  VARIABLES  //////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

boolean rf_start = false;
int rf_light = 0;
int rf_prevlight = 0;
int rf_counter = 0;
const int rf_loops = 25;
unsigned long rf_time = 0;


////////////////////////////////////////////////////////////////////
////  GAME  ///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

void ReactionF() {
  /* Start game by touching light 0 */
  if(getSensor(0) != 0 && !rf_start) {   
    /* Blink light 0 with 1 sec delay */
    if(wait(1000))
      lightOn(0,Colors(5));
    if(wait(1000))
      lightOff(0);
    
  }
  
  /* Turn light 0 off and turn random light on */
  else if(getSensor(0) == 0 && !rf_start) {
    lightOff(0);
      
    /* Save ID of ligt to be turned on */
    rf_light = random(LEDs);
    rf_prevlight = rf_light;
      
    /* One random light with random color */
    lightOn(rf_light,Colors(random(16)));
        
    rf_start = true;
    
    /* Save start time of game */
    rf_time = time;
  }
  
  /* New field and color */
  if(rf_light == getSensor(rf_light) && rf_start) {    
    lightOff(rf_light);
      
    rf_light = random(LEDs);
      
    /* Never get same light twice */
    while(rf_light == rf_prevlight) {
      rf_light = random(LEDs);
    }
      
    /* Save last light */
    rf_prevlight = rf_light;
        
    lightOn(rf_light,Colors(random(16)));
        
    /* Count fields */
    rf_counter++;
    
    /* Stop game */    
    if(rf_counter >= rf_loops) {
      allLightsOff(LEDs);
      
      /* Reset everything */
      rf_start = false;
      rf_counter = 0;
      rf_light = 0;
      rf_prevlight = 0;
      
      /* Time to complete the game */
      rf_time = time - rf_time;
      
      /* Send time to tablet */
      //write(rf_time);
      
      rf_time = 0;
    }
  }
}
