/*
const int nleds;
static WS2812 ledstrip;
static Pixel_t pixels[nleds];
*/



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

void colormix(){

  
}

void initializeLEDs(){
  ledstrip.init(NUM_LEDS);
}

/*
unsigned int channel_start = 0;
unsigned int channel_width = 1;
byte channel_buffer[128*3];
static Pixel_t pixels[nleds];
*/
void ArtnetToLeds(){
  uint8_t i;
  uint8_t buffer_i = 0;
  for (i=0; i<nleds; i++){
    //GRB järjestys
    pixels[i].R = channel_buffer[channel_start+(buffer_i*3)+1];
    pixels[i].G = channel_buffer[channel_start+(buffer_i*3);
    pixels[i].B = channel_buffer[channel_start+(buffer_i*3)+2];
    buffer_i += 3;
    //Jos paketteja on tullu vähemmän kuin ledejä, loopataan saatuja värejä ledeille
    if (buffer_i = (channel_width*3)) buffer_i = 0;
  }
  ledstrip.show(pixels);
}

void RGBtoLeds(){
  for (i=0; i<nleds; i++){
    //GRB järjestys
    pixels[i].R = simpleRGB_r;
    pixels[i].G = simpleRGB_g;
    pixels[i].B = simpleRGB_b
  }
  ledstrip.show(pixels);
  simpleRGB_change = false;
}

/*
//0 Default     Artnet in, leds out.
//1 simpleRGB   Users sets all leds to same R,G,B values
//2 RainbowFade Colorful demo animation
byte operation_mode = 0;
*/
void UpdateLeds(){
  if(operation_mode = 0){
  }else if (operation_mode == 1){
  }else if (operation_mode == 2){
  }
}
