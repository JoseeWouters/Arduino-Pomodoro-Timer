#include <Adafruit_NeoPixel.h>

#define NUM_PIXELS 12 // amount of LED

unsigned long interval = 3000;  // the time we need to wait
unsigned long previousMillis = 0;

uint32_t currentColor;// current Color in case we need it
uint32_t red;
uint16_t currentPixel = 0;// what pixel are we operating on

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, 2, NEO_GRB + NEO_KHZ800);

int piezoPin = 6;

int startButton = 12;
int buttonState = 0;

void setup() {
  pinMode(startButton, INPUT_PULLUP);
  currentColor = strip.Color(0,255,0);
  currentPixel = 0;
  strip.begin();
  strip.setBrightness(15);
  strip.show(); // Initialize all pixels to 'off'
}

void loop(){
  
buttonState = digitalRead(startButton);
  if(buttonState == HIGH) {
    pomodoro();
  }
}

void pomodoro(){
  if ((unsigned long)(millis() - previousMillis) >= interval) {
    previousMillis = millis();
    strip.setPixelColor(currentPixel,currentColor);
    strip.show();
    currentPixel++;
    tone(piezoPin, 100, 200);
    if(currentPixel > NUM_PIXELS){
      timesUp();
    }
    almostTime();
    }
}

void almostTime() {
  if(currentPixel >= 9) {
    currentColor = strip.Color(255,0,0);
  }
}

void timesUp() {
    for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i,0,0,0);
  }
  strip.show();
  tone(piezoPin, 500, 200);
  delay(300);
  tone(piezoPin, 700, 300);
  delay(300);
  tone(piezoPin, 900, 700);
  delay(700);
  exit(0);
}