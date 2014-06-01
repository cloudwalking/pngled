#include <Adafruit_NeoPixel.h>

#include "data.h"

#define LED_COUNT 18
#define LED_DATA_PIN 3
#define LED_DEFAULT_BRIGHTNESS 40

Adafruit_NeoPixel _pixels = Adafruit_NeoPixel(LED_COUNT, LED_DATA_PIN, NEO_GRB + NEO_KHZ400);

int32_t _frame;

void setup() {
  Serial.begin(9600);

  _frame = 0;
}

void loop() {
  Serial.print(data[_frame][0].red);
  Serial.print(", ");
  Serial.print(data[_frame][0].green);
  Serial.print(", ");
  Serial.println(data[_frame][0].blue);
  
  if (++_frame == RGAM_DATA_COLUMNS) _frame = 0;
  
  delay(50);
}
