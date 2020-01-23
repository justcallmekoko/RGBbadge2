#include "Patterns.h"
#include "Battery.h"

extern Adafruit_NeoPixel strip;
extern Battery batteryObj;

// Adjust values specific for a certain pattern
void Patterns::initPattern(uint8_t pattern)
{
  /*if (pattern == PULSE)
  {
    fade->delay = 20;
    fadeRate = 0.90;
    //this->Pulse(255, 255, 0);
  }*/
  if (pattern == TWINKLE)
  {
    this->Twinkle(3, 20, 0.95, 15);
  }
  else if (pattern == TRACER)
  {
    // (int ring_speed, int fade_delay, float fadeRate)
    this->Tracer2(15, 5, 0.96);
  }
  else if (pattern == FALLING_RAINBOW)
  {
    // (int ring_speed, int fade_delay, float fadeRate, int wheel_speed)
    this->Rainbow2(35, 2, 0.90, 2);
  }
  else if (pattern == BATTERY)
  {
    this->displayBatteryLevel();
  }
}

void Patterns::displayBatteryLevel()
{
  this->current_itter++;
  if (this->current_itter >= IP5306_CHECK_INTERVAL)
  {
    int8_t temp_level = batteryObj.getBatteryLevel();
  
    if (batteryObj.current_level != temp_level)
    {
      batteryObj.current_level = temp_level;
  
      float num_pixel = (Pixels * batteryObj.current_level) / 100;

      Serial.print("Updating battery display: ");
      Serial.print(batteryObj.current_level);
      Serial.print("% | Pixels: ");
      Serial.println(num_pixel);
  
      for (int i = 0; i < Pixels; i++)
      {
        if (i < num_pixel)
          strip.setPixelColor(i, 255, 255, 255);
        else
          strip.setPixelColor(i, 0, 0, 0);
      }
      strip.show();
    }
    this->current_itter = 0;
  }
}

/*
// Pulse a color on and off
void Patterns::Pulse(int r, int g, int b)
{
  if (this->show_led)
  {
    float modifier = 0;
    
    if (this->current_fade_itter > fade->delay)
    {
      if (this->increasing)
        modifier = 2 - fadeRate;
      else
        modifier = fadeRate;
  
      for(uint16_t l = 0; l < Pixels; l++)
      {
        this->redStates2[l] = this->redStates2[l] * modifier;
        
  
        this->greenStates2[l] = this->greenStates2[l] * modifier;
  
        
        this->blueStates2[l] = this->blueStates2[l] * modifier;
  
        if (this->redStates2[l] < 1 && this->greenStates2[l] < 1 && this->blueStates2[l] < 1)
        {
          this->increasing = true;
          this->redStates2[l] = r * 0.0037;
          this->greenStates2[l] = g * 0.0037;
          this->blueStates2[l] = b * 0.0037;
        }
        else if (this->redStates2[l] >= 255 || this->greenStates2[l] >= 255 || this->blueStates2[l] >= 255)
        {
          this->increasing = false;
          this->redStates2[l] = r;
          this->greenStates2[l] = g;
          this->blueStates2[l] = b;
        }
        
        strip.setPixelColor(l, this->redStates2[l], this->greenStates2[l], this->blueStates2[l]);
      }
      
      this->current_fade_itter = 0;
  
      /*
      Serial.print(redStates2[0]);
      Serial.print(" ");
      Serial.print(greenStates2[0]);
      Serial.print(" ");
      Serial.println(blueStates2[0]); 
      */  
      /* 
    }
    
    this->current_fade_itter++;
    
    strip.show();
  }
}*/

// Seamless Rainbow Ring
void Patterns::Rainbow2(int ring_speed, int fade_delay, float fadeRate, int wheel_speed)
{
  //this->current_itter = current_itter + wheel_speed;
  //if (current_itter >= 256)
  //  current_itter = 0;
    
  for(uint16_t i = 0; i < Pixels; i++) {
    //strip.setPixelColor(i, Wheel(((strip.numPixels() / (i + 1))+current_itter) & 255));
    //strip.setPixelColor(i, this->Wheel(((i * i) * 256 / 50 + this->wheel_pos) % 256));
    strip.setPixelColor(i, this->Wheel(((i) * 256 / Pixels + this->wheel_pos) % 256));
  }
  strip.show();
  delay(ring_speed);

  // Reverse
  //this->wheel_pos = this->wheel_pos + this->wheel_speed;
  //if (this->wheel_pos >= 256)
  //  this->wheel_pos = 0;

  // Forwards
  this->wheel_pos = this->wheel_pos - wheel_speed;
  if (this->wheel_pos < 0)
    this->wheel_pos = 255;
}

void Patterns::resetWheel()
{
  for(uint16_t l = 0; l < Pixels; l++) {
    this->redStates2[l] = 0;
    this->greenStates2[l] = 0;
    this->blueStates2[l] = 0;
    //this->redStates2[l] = 0;
    //this->greenStates2[l] = 0;
    //this->blueStates2[l] = 0;
    strip.setPixelColor(l, this->redStates2[l], this->greenStates2[l], this->blueStates2[l]);
    //strip.setPixelColor(l, this->redStates2[l], this->greenStates2[l], this->blueStates2[l]);
  }
  strip.show();
}


void Patterns::Twinkle(int ring_speed, int fade_delay, float fadeRate, int max_interval)
{
  this->current_itter++;
  if (this->current_itter >= ring_speed)
  {
    this->current_itter = 0;

    if (random(max_interval) == 1) {
      uint8_t i = random(Pixels);
      if (this->redStates2[i] < 1 && this->greenStates2[i] < 1 && this->blueStates2[i] < 1) {
        this->redStates2[i] = random(256);
        this->greenStates2[i] = random(256);
        this->blueStates2[i] = random(256);
      }
    }
  }

  if (this->current_fade_itter > fade_delay)
  {
    this->current_fade_itter = 1;
    for(uint16_t l = 0; l < Pixels; l++) {
      if (this->redStates2[l] > 1 || this->greenStates2[l] > 1 || this->blueStates2[l] > 1) {
        strip.setPixelColor(l, this->redStates2[l], this->greenStates2[l], this->blueStates2[l]);
        
        if (this->redStates2[l] > 1) {
          this->redStates2[l] = this->redStates2[l] * fadeRate;
        } else {
          this->redStates2[l] = 0;
        }
        
        if (this->greenStates2[l] > 1) {
          this->greenStates2[l] = this->greenStates2[l] * fadeRate;
        } else {
          this->greenStates2[l] = 0;
        }
        
        if (this->blueStates2[l] > 1) {
          this->blueStates2[l] = this->blueStates2[l] * fadeRate;
        } else {
          this->blueStates2[l] = 0;
        }
        
      } else {
        strip.setPixelColor(l, 0, 0, 0);
      }
    }
  }
  this->current_fade_itter++;
  strip.show();
}


void Patterns::Tracer2(int ring_speed, int fade_delay, float fadeRate)
{
  int r = 255;
  int g = 0;
  int b = 255;
  current_itter++;
  if (current_itter >= ring_speed * fade_delay)
  {   
    current_itter = 0;
    current_pixel++;
    if (current_pixel >= Pixels)
      current_pixel = 0;
      
    uint16_t i = current_pixel;
    if (redStates2[i] < 1 && greenStates2[i] < 1 && blueStates2[i] < 1) {
      redStates2[i] = r;
      greenStates2[i] = g;
      blueStates2[i] = b;
    }
  }

  if (current_fade_itter > fade_delay)
  {
    current_fade_itter = 1;
    
    for(uint16_t l = 0; l < Pixels; l++) {
      if (redStates2[l] > 1 || greenStates2[l] > 1 || blueStates2[l] > 1) {
        strip.setPixelColor(l, redStates2[l], greenStates2[l], blueStates2[l]);
        
        if (redStates2[l] > 1) {
          redStates2[l] = redStates2[l] * fadeRate;
        } else {
          redStates2[l] = 0;
        }
        
        if (greenStates2[l] > 1) {
          greenStates2[l] = greenStates2[l] * fadeRate;
        } else {
          greenStates2[l] = 0;
        }
        
        if (blueStates2[l] > 1) {
          blueStates2[l] = blueStates2[l] * fadeRate;
        } else {
          blueStates2[l] = 0;
        }
        
      } else {
        strip.setPixelColor(l, 0, 0, 0);
      }
    }
  }
  //strip.setPixelColor(0, 0, 255, 0);
  //strip.setPixelColor(11, 255, 0, 0);
  strip.show();
  
  current_fade_itter++;
  
  //delay(10);
}

uint32_t Patterns::Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
