//########################## Pin define #####################
const unsigned int PIN_ENCODER_CLK = 5;  // Connected to CLK on KY-040
const unsigned int PIN_ENCODER_DT = 4;  // Connected to DT on KY-040

//########################## Channel Data ###################
unsigned int channel_start = 0;
unsigned int channel_width = 1;
unsigned byte channel_buffer[128*3];

//########################## Modes ##########################
// simpleRGB
bool simpleRGB_enable = false;
unsigned byte simpleRGB_r = 255;
unsigned byte simpleRGB_g = 255;
unsigned byte simpleRGB_b = 255;
// raindbow fade
bool rainbow_fade_enabled = false;

//########################## Display ########################
bool display_update_required = true;

//########################## Adjustments ####################
//Kanavilta tulleet rgb arvot kerrotaan tällä. arvo*brightness/100
unsigned byte brightness = 100; //0-100%

//########################## Input ##########################
signed int encoder_movement = 0;
bool encoder_clk_current = 0;
bool encoder_clk_last = 0;
bool encoder_dt_current = 0;
bool encoder_dt_last = 0;
bool button_pressed = false;
bool button_changed = false;

//######################## Networking  ######################
//udp databuffer etc?

//###########################################################

void setup() { 
 pinMode (PIN_ENCODER_CLK,INPUT);
 pinMode (PIN_ENCODER_DT,INPUT);
 encoder_dt_last = digitalRead(PIN_ENCODER_DT);

 Serial.begin (9600);
 Serial.println("Starting.");
}

//Päivitetään input laitteiden tila ja palautetaan true,
//jos jotain on muuttunut.
bool UpdateInput(){
    return true;
}

void loop() {
    //Tähän loopin nopeuden säätö

    if (UpdateInput()){
        UpdateMenu();
    }

    if ( display_update_required ){
        //jos tarpeeksi aikaa kulunut viime lcd päivityksestä, päivitetään lcd.
    }
       
} 
