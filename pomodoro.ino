#include <Adafruit_NeoPixel.h>

#define NUM_PIXELS 12 // amount of LED

unsigned long interval = 60000;  // the time we need to wait
unsigned long previousMillis = 0;

uint32_t currentColor;// current Color in case we need it
uint32_t red;
uint16_t currentPixel = 0;// what pixel are we operating on

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, 2, NEO_GRB + NEO_KHZ800);

void setup() {
  currentColor = strip.Color(0,255,0);
  currentPixel = 0;
  strip.begin();
  strip.setBrightness(15);
  strip.show(); // Initialize all pixels to 'off'
}

// Basic idea. You could reorg and pass pixel index and color as a function - or you could go through a gradient of colors.
void loop(){
if ((unsigned long)(millis() - previousMillis) >= interval) {
  previousMillis = millis();
  colorWipe();
 }
}

void colorWipe(){
  strip.setPixelColor(currentPixel,currentColor);
  strip.show();
  currentPixel++;
  if(currentPixel > NUM_PIXELS){
    timesUp();
  }
  almostTime();
}

void almostTime() {
  if(currentPixel >= 9) {
    currentColor = strip.Color(255,0,0);
  }
}

void timesUp() {
    for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i,0,0,0); //blue
  }
  strip.show();
}