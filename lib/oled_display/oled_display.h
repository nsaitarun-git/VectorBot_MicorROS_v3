#ifndef OLED_ARROWS_H
#define OLED_ARROWS_H
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

// Display object
extern Adafruit_SH1106G display;

void displayArrow(String request);
#endif