#include <Wire.h> //I2C kommunikointi
#include <hd44780.h>//hd44780 ajuri (LCD)
#include <hd44780ioClass/hd44780_I2Cexp.h> //i2c expander ajuri lcd:lle
#include <user_interface.h>

#include <ws2812_i2s.h>



//#ifndef INPUT 

//########################## Pin define #####################
const unsigned int PIN_ENCODER_CLK = 14;  // Connected to CLK on KY-040
const unsigned int PIN_ENCODER_DT = 12;  // Connected to DT on KY-040
const unsigned int PIN_ENCODER_BUTTON = 0;  // Connected to SW on KY-040"
/*
const unsigned int PIN_LCD_SDA = 4; //connected to SDA on the i2c expander
const unsigned int PIN_LCD_SCL = 5; //connected to SCL on the i2c expanders
*/

/*
I2s inteface ledejä varten
PinName PinNum  IO    Function Name
MTDO    13      IO15  I2SO_BCK
U0RXD   25      IO3   I2SO_DATA
GPIO2   14      IO2   I2SO_WS
*/

//#define INPUT 

//########################## Input ##########################
signed int encoder_movement = 0;    //Amount of ticks rotated
//int encoder_movement_last=0; For input determination
signed int encoder_accelerated = 0; //Rotation + acceleration
//helpers variables
bool encoder_clk_current = false;
bool encoder_clk_last = false;
bool button_pressed_current = false;
bool button_pressed_last = false;
//button trigger
bool button_falling_edge = false;
int encoder_dt_last;

//Käytetään encoder kiihtyvyyteen
unsigned long lastTickMillis = 0;
signed int ticks;

unsigned long buttonLastMillis = 0;
unsigned long buttonDeBounceInterval = 2;

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

//#endif

//########################## Channel Data ###################
unsigned int channel_start = 0;
unsigned int channel_width = 1;
byte channel_buffer[128*3];

//########################## Modes ##########################
//0 Default     Artnet in, leds out.
//1 simpleRGB   Users sets all leds to same R,G,B values
//2 RainbowFade Colorful demo animation
byte operation_mode = 1;
// simpleRGB
byte simpleRGB_r = 60;;
byte simpleRGB_g = 0;
byte simpleRGB_b = 70;//128;
bool simpleRGB_change = true; //Set false when change led colour. //set true when input changes
// raindbow fade
byte rainbow_fade_speed = 0;

//########################## Display ########################
bool display_update_required = true;
unsigned long lcd_update_next = 0; //ms
const unsigned int lcd_update_frequency = 500; //ms
const unsigned int LCD_COLS = 16;
const unsigned int LCD_ROWS = 2;
hd44780_I2Cexp lcd;



//########################## Adjustments ####################
//Kanavilta tulleet rgb arvot kerrotaan tällä. arvo*brightness/100
byte brightness = 100; //0-100%

//######################## Networking  ######################
//udp databuffer etc?

//######################## Interrupt service #############################
//interrupt service frequency and variables

const unsigned int interrupt_frequency = 20; // 20 ms for 50 hZ

os_timer_t interrupt_timer; //interrupt ajastin

bool interrupt_test = false; //muuttuja interruptin testausta varten

bool new_artnet_data; // is new artnet data being received

unsigned long new_interrupt = 0;

//######################## Menu #############################
//Sisältää menun tuottaman char arrayn, joka pusketaan lcd-ruudulle.
char menu_lcd_projection[16*2];
char menu_lcd_projection_row2[16];
int menu_state=6;
bool menu_update_required = true;
bool selection=false; //muutetaanko arvoa vai liikutaanko menussa
//######################## Miscellanneous #####################
unsigned long mainloop_next_update = 0;
const unsigned int mainloop_max_frequency = 10; //ms

unsigned long current_time = 0;
//bool debugging = false;
//###########################################################
//###################Randomness##############################
int i = 0;
char rand_buffer[10240]; // Buffer must be multiple of 4 your you might have a bad time
//###########################################################
//################### LEDS     ##############################
const int nleds=8;
static WS2812 ledstrip;
static Pixel_t pixels[nleds];

//###########################################################

