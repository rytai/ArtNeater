
#ifndef INPUT 
#include "definitions.h"
#include "Arduino.h"

#define INPUT 

//########################## Input ##########################
signed int encoder_movement = 0;    //Amount of ticks rotated
signed int encoder_accelerated = 0; //Rotation + acceleration
//helpers variables
bool encoder_clk_current = false;
bool encoder_clk_last = false;
bool button_pressed_current = false;
bool button_pressed_last = false;
//button trigger
bool button_falling_edge = false;

//Päivitä encoderin sijainti ja palauta onko se muuttunut
//Käytetään vain UpdateInput -funktiossa.
bool InputEncoderHasChanged();
bool InputButtonHasChanged();

//Päivitetään input laitteiden tila
//palauttaa true, jos jotain on muuttunut.
bool UpdateInput();

//Tähän tulee encoderin kiihtyvyyden käsittely
//Menu luokassa kutsutaan tätä
signed int GetEncoderMovement();

#endif
