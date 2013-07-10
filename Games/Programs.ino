void LightTest_1() {
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
