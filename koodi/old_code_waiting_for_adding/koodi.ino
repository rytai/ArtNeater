//LCD
#include <Wire.h> //I2C kommunikointi
#include "definitions.h" //Pin definition
#include "input.h" //Encoderin syötteet
#include "output.h" //30.11. lcdnäytön tulosteet



//########################## Channel Data ###################
unsigned int channel_start = 0;
unsigned int channel_width = 1;
unsigned byte channel_buffer[128*3];

//########################## Modes ##########################
//0 Default     Artnet in, leds out.
//1 simpleRGB   Users sets all leds to same R,G,B values
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

//######################## Interrupt service #############################
//interrupt service frequency and variables

const unsigned int interrupt_frequency = 2; // 2 ms for 500 hZ

bool new_artnet_data; // is new artnet data being received

unsigned long new_interrupt = 0;

//######################## Menu #############################
//Sisältää menun tuottaman char arrayn, joka pusketaan lcd-ruudulle.
char menu_lcd_projection[16*2];
//######################## Miscellanneous #####################
unsigned long mainloop_next_update = 0;
const unsigned int mainloop_max_frequency = 1; //ms

unsigned long current_time = 0;
//###########################################################

void setup() { 
    //Alustetaan GPIO pinnit
    pinMode (PIN_ENCODER_CLK,INPUT);
    pinMode (PIN_ENCODER_DT,INPUT);
	pinMode (PIN_ENCODER_BUTTON,INPUT);
	pinMode (PIN_LCD_SDA,OUTPUT);
	pinMode (PIN_LCD_SCL,OUTPUT);

    //Alustetaan laitteisiin liittyvät muuttujat
    encoder_dt_last = digitalRead(PIN_ENCODER_DT);

    //Aloitetaan serial debugging
    Serial.begin (9600);
    Serial.println("Starting.");

	//alustetaan lcd-näyttö
	int status = lcd.begin(LCD_COLS, LCD_ROWS);
  if (status) // non zero status means it was unsuccesful
  {
    status = -status; // convert negative status value to positive number

    // begin() failed so blink error code using the onboard LED if possible
    hd44780::fatalError(status); // does not return
  }

  // initalization was successful, the backlight should be on now

  // Print a message to the LCD
  lcd.print("Hello, World!");

    //Alustetaan ajanotot
    lcd_update_next = millis();
    mainloop_next_update = millis();
}

//Sisältää menutoiminnot
//Palauttaa true, jos menu on muuttunut -> seuraa lcd päivitys
bool UpdateMenu(){
    return true;
}

//void UpdateLCD(){} moved to output.c

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
