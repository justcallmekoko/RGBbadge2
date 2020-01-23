#include "Patterns.h"
#include "Battery.h"
//#include "ButtonInput.h"


Adafruit_NeoPixel strip = Adafruit_NeoPixel(Pixels, PIN, NEO_GRB + NEO_KHZ800);

Patterns patternObj;
Battery batteryObj;
//ButtonInput buttonObj;

bool current_button_state = false;

void setup() {
  Serial.begin(115200);

  Serial.println(F("\n\nRunning...\n\n"));

  pinMode(3, INPUT);
  
  strip.begin();
  strip.setBrightness(50);
  strip.show();

  // Test XY function
  //strip.setPixelColor(mapObj.XY(1, 0), strip.Color(255, 255, 255));
  //strip.setPixelColor(mapObj.XY(1, 1), strip.Color(255, 255, 255));
  //strip.setPixelColor(mapObj.XY(0, 1), strip.Color(255, 255, 255));
  //strip.show();

  if (batteryObj.checkIP5306I2C())
    Serial.println("IP5306 I2C Capable: true");
  else
    Serial.println("Bruh");
  
  delay(100);
}

void loop()
{
  //buttonObj.checkPatternChange();
  if (digitalRead(3) == 1)
  {
    if (!current_button_state)
    {
      batteryObj.current_level = 0;
      current_button_state = true;
      patternObj.currentPattern++;
      if (((patternObj.currentPattern >= NUM_PATTERN) && (batteryObj.ip5306_i2c_capable)) || 
          ((patternObj.currentPattern >= NUM_PATTERN - 1) && (!batteryObj.ip5306_i2c_capable)))
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
