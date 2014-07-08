#include <Adafruit_NeoPixel.h>

#include "data.h"

#define LED_COUNT 50 // should equal RGAM_DATA_ROWS
#define LED_DATA_PIN 3
#define LED_DEFAULT_BRIGHTNESS 10
#define DELAY 50

Adafruit_NeoPixel _pixels = Adafruit_NeoPixel(LED_COUNT, LED_DATA_PIN, NEO_GRB + NEO_KHZ800);

int32_t _frame;

void setup() {
  Serial.begin(9600);
  
  _pixels.begin();
  _pixels.setBrightness(LED_DEFAULT_BRIGHTNESS);

  _frame = 0;
}

void loop() {
  Serial.print("frm "); Serial.println(_frame);

  for (int32_t row = 0; row < RGAM_DATA_ROWS; row++) {
    if (row >= LED_COUNT) break;

    byte *pixel = data[_frame][row];

    uint16_t red   = (int) pgm_read_byte(pixel);
    uint16_t green = (int) pgm_read_byte(&(pixel[1]));
    uint16_t blue  = (int) pgm_read_byte(&(pixel[2]));
    
    uint32_t color = _pixels.Color(red, green, blue);

    _pixels.setPixelColor(row, color);
  }
  _pixels.show();
  
  if (++_frame == RGAM_DATA_COLUMNS) _frame = 0;
  
  delay(DELAY);
  Serial.println();
}
