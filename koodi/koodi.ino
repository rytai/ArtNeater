//LCD
#include <Wire.h> //I2C kommunikointi
#include <hd44780.h>//hd44780 ajuri (LCD)
#include <hd44780ioClass/hd44780_I2Cexp.h> //i2c expander ajuri lcd:lle
#include "definitions.h" //Pin definition
#include "input.h" //Encoderin syötteet

//########################## Channel Data ###################
unsigned int channel_start = 0;
unsigned int channel_width = 1;
unsigned byte channel_buffer[128*3];

//########################## Modes ##########################
//0 Default     Artnet in, leds out.
//1 simpleRPG   Users sets all leds to same R,P,G values
//2 RainbowFade Colorful demo animation
unsigned byte operation_mode = 0;
// simpleRGB
unsigned byte simpleRGB_r = 255;
unsigned byte simpleRGB_g = 255;
unsigned byte simpleRGB_b = 255;
// raindbow fade
unsigned byte rainbow_fade_speed = 0;

//########################## Display ########################
bool display_update_required = true;
unsigned long lcd_update_next = 0; //ms
const unsigned int lcd_update_frequency = 100; //ms
const unsigned int LCD_COLUMNS = 16;
const unsigned int LCD_ROWS = 2;

//########################## Adjustments ####################
//Kanavilta tulleet rgb arvot kerrotaan tällä. arvo*brightness/100
unsigned byte brightness = 100; //0-100%

//######################## Networking  ######################
//udp databuffer etc?

//######################## Menu #############################
//Sisältää menun tuottaman char arrayn, joka pusketaan lcd-ruudulle.
char menu_lcd_projection[16*2];
//######################## Misclanneous #####################
unsigned long mainloop_next_update = 0;
const unsigned int mainloop_max_frequency = 1; //ms
unsigned long current_time = 0;
//###########################################################

void setup() { 
    //Alustetaan GPIO pinnit
    pinMode (PIN_ENCODER_CLK,INPUT);
    pinMode (PIN_ENCODER_DT,INPUT);

    //Alustetaan laitteisiin liittyvät muuttujat
    encoder_dt_last = digitalRead(PIN_ENCODER_DT);

    //Aloitetaan serial debugging
    Serial.begin (9600);
    Serial.println("Starting.");

    //Alustetaan ajanotot
    lcd_update_next = millis();
    mainloop_next_update = millis();
}

//Sisältää menutoiminnot
//Palauttaa true, jos menu on muuttunut -> seuraa lcd päivitys
bool UpdateMenu(){
    return true;
}

void UpdateLCD(){
}

void loop() {
    //Testataan onko kulunut tarpeeksi aikaa viimeisestä loopin läpikäynnistä
    current_time = millis();
    if (current_time >= mainloop_next_update){
        mainloop_next_update = current_time + mainloop_max_frequency;

        //Testataan syöttölaitteet ja kutsutaan menun päivitystä jos jokin syöte on muuttunut
        if ( UpdateInput() ){
            //jos menu muuttunut -> Merkataan lcd näyttö päivitettäväksi
            display_update_required = UpdateMenu();
        }
        //jos tarpeeksi aikaa on kulunut viime lcd päivityksestä -> päivitetään lcd
        if ( display_update_required && (millis() >= lcd_update_next) ){
            lcd_update_next += lcd_update_frequency;
            UpdateLCD();
        }
    }
} 
