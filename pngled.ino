#include <Adafruit_NeoPixel.h>

#include "data.h"

#define LED_COUNT 8
#define LED_DATA_PIN 3
#define LED_DEFAULT_BRIGHTNESS 10

Adafruit_NeoPixel _pixels = Adafruit_NeoPixel(LED_COUNT, LED_DATA_PIN, NEO_GRB + NEO_KHZ800);

int32_t _frame;

void setup() {
  Serial.begin(9600);
  
  _pixels.begin();
  _pixels.setBrightness(LED_DEFAULT_BRIGHTNESS);

  _frame = 0;
}

void loop() {
  Serial.println(_frame);
  for (int row = 0; row < RGAM_DATA_ROWS; row++) {
    if (row >= LED_COUNT) break;

    uint16_t red   = (int)data[_frame][row].red;
    uint16_t green = (int)data[_frame][row].green;
    uint16_t blue  = (int)data[_frame][row].blue;
    Serial.println(red);
    
    uint32_t color = _pixels.Color(red, green, blue);

    _pixels.setPixelColor(row, color);
  }
  
  _pixels.show();
  Serial.println();
  
  
  if (++_frame == RGAM_DATA_COLUMNS) _frame = 0;
  
  delay(40);
}
