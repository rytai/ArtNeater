#include "definitions.h"
#include "Arduino.h"

#ifndef DISPLAY
#define DISPLAY

//########################## Display ########################
//Asetetaan pääloopissa menua päivitettäessä
bool display_update_required = true; 
const unsigned int LCD_COLUMNS = 16;
const unsigned int LCD_ROWS = 2;

void UpdateLCD();

#endif
