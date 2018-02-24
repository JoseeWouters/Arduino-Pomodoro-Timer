#include <Adafruit_NeoPixel.h>

#define NUM_PIXELS 12 // amount of LED

unsigned long interval = 60000;  // the time we need to wait
unsigned long previousMillis = 0;

uint32_t currentColor;// current Color in case we need it
uint32_t red;
uint16_t currentPixel = 0;// what pixel are we operating on

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, 2, NEO_GRB + NEO_KHZ800);

int ledButton = 11;

int startButton = 12;
int buttonState = LOW;
int reading;
int previous = HIGH;

long time = 0;
long debounce = 500;

void setup() {
  pinMode(startButton, INPUT_PULLUP);
  pinMode(ledButton, OUTPUT);
  currentColor = strip.Color(0,255,0);
  currentPixel = 0;
  strip.begin();
  strip.setBrightness(15);
  strip.show(); // Initialize all pixels to 'off'
}

void loop(){

  reading = digitalRead(startButton);

  if (reading == HIGH && previous == LOW && (millis() - time) > debounce) {
    if (buttonState == HIGH) {
      buttonState = LOW;
    } else if (buttonState == LOW) {
      buttonState = HIGH;
    }
    time = millis();
  }
  previous = reading;

  if (buttonState == HIGH) {
    digitalWrite(ledButton, HIGH);
    pomodoro();
    timesUp();
    buttonState = LOW;
  } 
  else if (buttonState == LOW) {
    digitalWrite(ledButton, LOW);
  }
}

void pomodoro(){
  
  unsigned long currentMillis = millis(); // grab current time

  for (uint16_t led = 0; led < strip.numPixels(); led++) {
    strip.setPixelColor(currentPixel,currentColor);
    strip.show();
    while (millis() < currentMillis + interval) {
      // do nothing!
    }
    currentPixel++;
    currentMillis = millis();
  }
  currentPixel = 0;
}

void timesUp() {
    for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i,0,0,0);
  }
  strip.show();
}