#include <Adafruit_NeoPixel.h>

#include "data.h"
#include "rgamRGB.h"

#define LED_COUNT 8
#define LED_DATA_PIN 3
#define LED_DEFAULT_BRIGHTNESS 10
#define DELAY 60

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

  for (int32_t row = 0; row < RGAM_DATA_ROWS; row++) {
    if (row >= LED_COUNT) break;

    rgamRGB pixel = data[_frame][row];

    uint16_t red   = pixel.red;
    uint16_t green = pixel.green;
    uint16_t blue  = pixel.blue;
    
    uint32_t color = _pixels.Color(red, green, blue);

    _pixels.setPixelColor(row, color);
  }
  _pixels.show();
  
  if (++_frame == RGAM_DATA_COLUMNS) _frame = 0;
  
  delay(DELAY);
  Serial.println();
}
