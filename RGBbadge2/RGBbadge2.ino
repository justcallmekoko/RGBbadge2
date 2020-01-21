#include "Patterns.h"
//#include "ButtonInput.h"


Adafruit_NeoPixel strip = Adafruit_NeoPixel(Pixels, PIN, NEO_GRB + NEO_KHZ800);

Patterns patternObj;
//ButtonInput buttonObj;
bool current_button_state = false;

void setup() {
  //Serial.begin(115200);

  //Serial.println(F("Running..."));

  pinMode(3, INPUT);
  
  strip.begin();
  strip.setBrightness(50);
  strip.show();

  // Test XY function
  //strip.setPixelColor(mapObj.XY(1, 0), strip.Color(255, 255, 255));
  //strip.setPixelColor(mapObj.XY(1, 1), strip.Color(255, 255, 255));
  //strip.setPixelColor(mapObj.XY(0, 1), strip.Color(255, 255, 255));
  //strip.show();
  delay(100);
}

void loop()
{
  //buttonObj.checkPatternChange();
  if (digitalRead(3) == 1)
  {
    if (!current_button_state)
    {
      current_button_state = true;
      patternObj.currentPattern++;
      if (patternObj.currentPattern >= NUM_PATTERN)
        patternObj.currentPattern = 0;
      //Serial.print("Changing pattern: ");
      //Serial.println(patternObj.currentPattern);
      
      patternObj.resetWheel();
    }
  }
  else
    current_button_state = false;
    
  patternObj.initPattern(patternObj.currentPattern);
}
