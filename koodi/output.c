#include "output.h"
#include <arduino.h>
#include <hd44780.h>//hd44780 ajuri (LCD)
#include <hd44780ioClass/hd44780_I2Cexp.h> //i2c expander ajuri lcd:lle

void lcdFlush()
{
	lcd.setCursor(0, 1);
	lcd.print("                  ");
}

void UpdateLCD()
{
	lcdFlush();
	lcd.setCursor(0, 1);
	lcd.print(menu_lcd_projection);
}


