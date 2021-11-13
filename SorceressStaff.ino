#include "FastLED.h"
#define LED_TYPE    WS2812B  //WS2811, WS2812, WS2812B
#define DATA_PIN 13
#define NUM_LEDS 10
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
#define BRIGHTNESS 255

uint8_t huePurple = 192;
uint8_t hueRed = 0;
uint8_t hueOrange = 15;
uint8_t hueLastRandom = 0;

uint8_t sat = 255;
uint8_t val = 0;


//---------------------------------------------------------------
void setup() {
 // Serial.begin(115200);  // Allows serial monitor output (check baud rate)
  delay(2000);  // Startup delay
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

//---------------------------------------------------------------
void loop() {

  if (digitalRead(2) == HIGH) {  //fade up
    if (val < 255) {
    EVERY_N_MILLISECONDS(9){
      hueLastRandom = pickRandomColor();  
      fill_solid( leds, NUM_LEDS, CHSV(hueLastRandom,sat,val+1) );
      val = val + 1;
      //Serial.println("HIGH " + val);
      }
    }
  }

  else if (digitalRead(2) == LOW) {  //fade down
    if (val > 0) {
    EVERY_N_MILLISECONDS(5){
      fill_solid( leds, NUM_LEDS, CHSV(hueLastRandom,sat,val-1) );
      val = val - 1;
    //  Serial.println(val);
      }
    }
  }
  
  FastLED.show();
  
}//end_main_loop

uint8_t pickRandomColor(){
  uint8_t randomColor = random(1,4);
  uint8_t returnColor = 0;
  switch(randomColor){
    case 1:
    returnColor = huePurple;
    break;
    case 2:
    returnColor = hueRed;
    break;
    case 3:
    returnColor = hueOrange;
    break;
   }
   return returnColor;
}
