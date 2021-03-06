#bin/python

from PIL import Image
import numpy
import sys

def printStringToFile(string, filename):
  file = open(filename, "w");
  file.write("/* Autogenerated by %s */\n" % (sys.argv[0]));
  file.write(string)
  file.close()

def constructHeaderFileText(columns, rows):
  string = """
#include <Arduino.h>
#include <avr/pgmspace.h>
#define RGAM_DATA_COLUMNS %s
#define RGAM_DATA_ROWS %s
#define RGAM_COLORS 3
extern byte data[RGAM_DATA_COLUMNS][RGAM_DATA_ROWS][RGAM_COLORS] PROGMEM;
""" % (str(columns), str(rows))
  return string

def constructDataFileText(image, headerFilename):
  string = """
#include "%s.h"
extern byte data[RGAM_DATA_COLUMNS][RGAM_DATA_ROWS][RGAM_COLORS] PROGMEM =
""" % headerFilename
  string += "{\n"
  
  columns = image.shape[1]
  
  for i in range(0, columns):
    string += " { // col " + str(i) + "\n"
    
    for row in image[ : ,i]:
      string += "  { "
      string += str(int(row[0])) + ", "
      string += str(int(row[1])) + ", "
      string += str(int(row[2]))
      string += " },\n"
    
    string += " },\n"
  
  string += "};\n"
  return string

if __name__ == "__main__":
  filename = "data.png"
  image = Image.open(filename);
  png = numpy.asarray(image)
  
  print png.shape
  
  columns = png.shape[1]
  rows = png.shape[0]
  
  header = constructHeaderFileText(columns, rows)
  printStringToFile(header, "data.h")
  
  data = constructDataFileText(png, "data");
  printStringToFile(data, "data.c");
