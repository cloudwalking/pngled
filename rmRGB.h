#ifndef DEFINE_rmRGB
#define DEFINE_rmRGB

#include "Arduino.h"
#include <avr/pgmspace.h>
struct rmRGB {
  prog_uchar red;
  prog_uchar green;
  prog_uchar blue;
};
typedef struct rmRGB rmRGB;

#endif
