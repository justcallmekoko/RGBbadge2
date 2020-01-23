#ifndef Patterns_h
#define Patterns_h

#include <Adafruit_NeoPixel.h>

//#ifdef __AVR__
//  #include <avr/power.h>
//#endif

#define PIN 2
#define Pixels 16


#define NUM_PATTERN 4

// Pattern definitions
#define FALLING_RAINBOW 0
//#define PULSE 2
#define TWINKLE 1
#define TRACER 2
#define BATTERY 3

//extern Adafruit_NeoPixel strip;

class Patterns
{
  private:
  
    // Ring Settings
    //int ring_speed = 6; // (ms * fade_delay)
    //int fade_delay = 20; // ms
    //int max_interval = 2; // TIME BETWEEN PIXELS FIRING ((0 - x) * 10ms)
    
    int current_itter = 6;
    int current_pixel = 0;
    int current_fade_itter = 1;
    int wheel_pos = 255;
    //int wheel_speed = 1; // lower = slower
    bool increasing = true;
    //int redStates[Pixels]; // supposed to be float but need to save space
    //int blueStates[Pixels];
    //int greenStates[Pixels];
    float redStates2[Pixels];
    float blueStates2[Pixels];
    float greenStates2[Pixels];
    //float fadeRate= 0.80;

    uint32_t Wheel(byte WheelPos);

  public:
    byte currentPattern PROGMEM = 0;
    
    // Color presets
    //float scanning[3] = {255, 6, 0};
    //float deauthing[3] = {255, 6, 0};
    //float serving[3] = {0, 170, 255};
    //float clicon[3] = {255, 255, 0};
    //float purple[3] = {255, 0, 255};

    void initPattern(uint8_t pattern);
    //void Pulse(int r, int g, int b);
    //void Rainbow1();
    void displayBatteryLevel();
    void Rainbow2(int ring_speed, int fade_delay, float fadeRate, int wheel_speed);
    void resetWheel();
    void Twinkle(int ring_speed, int fade_delay, float fadeRate, int max_interval);
    //void Tracer(int r, int g, int b);
    void Tracer2(int ring_speed, int fade_delay, float fadeRate);
};

#endif
