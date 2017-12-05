#ifndef OUTPUT

#include "definitions.h"
#include <hd44780.h>//hd44780 ajuri (LCD)
#include <hd44780ioClass/hd44780_I2Cexp.h> //i2c expander ajuri lcd:lle
#include <arduino.h>

#define OUTPUT

hd44780_I2Cexp lcd;

void UpdateLCD();
void lcdFlush();


#endif
