//Kaikkien tulee olla saman pituisia.
const int headerLenght = 11;
const char hBrightness[] = "Brightness:";
const char hDMXch[]    =   "DMX ch:    ";
const char hLEDcount[]   = "LED count: ";
const char hOpMode[] =     "Mode:      ";
const char hManualR[] =    "Manual R:  ";
const char hManualB[] =    "Manual B:  ";
const char hManualG[] =    "Manual G:  ";
const char hWifi[]=        "Wifi:      ";
const char hDemo[]=        "Demo:      ";

//Siirtää headerLenght määrän kirjaimia annetusta arraysta menu_lcd_projection arrayyn.
void putHeader(const char * headerText){
  for(int i = 0; i < headerLenght; i++){
    menu_lcd_projection[i] = headerText[i];
  }
  for(int i = headerLenght; i < 32; i++){
    menu_lcd_projection[i] = ' ';
  }
}

//Muuntaa annetun tavun char-arvoksi ja vie sen arrayyn.
void putValue(int val){
  int valuePosition;
  char valueAsChar[3];
  int digits;
  if (val < 10){
    digits = 1;
    valuePosition = 14;
  }
  else if (val < 100){
    digits = 2;
    valuePosition = 13;
  }
  else {
    digits = 3;
    valuePosition = 12;
  }
  //"Tulostaa" numeron char arrayhyn
  sprintf(valueAsChar, "%d", val);
  if(debugging) Serial.println("testi");
  menu_lcd_projection[i+0] = ' ';
  menu_lcd_projection[i+1] = ' ';
  menu_lcd_projection[i+2] = ' ';
  for(int i = 0; i < digits; i++){
    menu_lcd_projection[i+valuePosition] = valueAsChar[i];
    if(debugging) Serial.print("Val as char ");
    if(debugging) Serial.println(valueAsChar[i]);
  }
}


void menuLCD(){
  
  //DMX address
  if(menu_state==0){
  putHeader(hDMXch);
  putValue(channel_start);                  
    
  }
  //LED count
  else if(menu_state==1){
  putHeader(hLEDcount);
  putValue(channel_width);
                        
  }
  //Operation mode
  else if(menu_state==2){

  putHeader(hOpMode);
  putValue(operation_mode);
  }
  //Max brightness
  else if(menu_state==3){
  putHeader(hBrightness);
  putValue(brightness);
  }
  //manual red
  else if(menu_state==4){
  putHeader(hManualR);
  putValue(simpleRGB_r);
  }
  //manual blue
  else if(menu_state==5){
  putHeader(hManualB);
  putValue(simpleRGB_b);  
  }
  //manual green
  else if(menu_state==6){
  putHeader(hManualG);
  putValue(simpleRGB_g);
  }
  //demo macro (placeholder)
  else if(menu_state==7){
  putHeader(hDemo);
   
  }
  //Wifi state and IP address (placeholder)
  else if(menu_state==8){
  putHeader(hWifi);
  
  }
}

bool UpdateMenu(){
  if(debugging) Serial.print("SELECTION: ");
  if(debugging) Serial.println(selection);
  if(selection){
    if(menu_state==0){
      if((channel_start > 0 && channel_start < 256) || (channel_start == 0 && encoder_movement > 0) || (channel_start == 256 && encoder_movement < 0))channel_start += encoder_movement;
    }
    else if(menu_state==1){
       if((channel_width > 1 && channel_width < 256) || (channel_width == 1 && encoder_movement > 0) || (channel_width == 256 && encoder_movement < 0))channel_width+= encoder_movement;
    }
    else if(menu_state==2){
       if((operation_mode > 0 && operation_mode < 2) || (operation_mode == 0 && encoder_movement > 0) || (operation_mode == 2 && encoder_movement < 0))operation_mode+= encoder_movement;
    }
    else if(menu_state==3){
      if((brightness > 0 && brightness < 100) || (brightness == 0 && encoder_movement > 0) || (brightness == 100 && encoder_movement < 0)) brightness+= encoder_movement;
    }
    else if(menu_state==4){
      simpleRGB_change = true;
      if((simpleRGB_r > 0 && simpleRGB_r < 256) || (simpleRGB_r == 0 && encoder_movement > 0) || (simpleRGB_r == 256 && encoder_movement < 0)) simpleRGB_r+= encoder_movement;
    }
    else if(menu_state==5){
      simpleRGB_change = true;
      if((simpleRGB_b > 0 && simpleRGB_b < 256) || (simpleRGB_b == 0 && encoder_movement > 0) || (simpleRGB_b == 256 && encoder_movement < 0)) simpleRGB_b+= encoder_movement;
    }
    else if(menu_state==6){
      simpleRGB_change = true;
      if((simpleRGB_g > 0 && simpleRGB_g < 256) || (simpleRGB_g == 0 && encoder_movement > 0) || (simpleRGB_g == 256 && encoder_movement < 0)) simpleRGB_g+= encoder_movement;
    }
    encoder_movement = 0;
  }
  else {
    menuSwitch();
  }
  menuLCD();
    return true;
}

void menuSwitch(){
if((menu_state < 6 && menu_state > 0 )|| (menu_state==0 && encoder_movement > 0) || (menu_state==6 && encoder_movement < 0))menu_state += encoder_movement;
/*if(encoder_movement>encoder_movement_last) menu_state++;
else if(encoder_movement<encoder_movement_last) menu_state--;
*/
encoder_movement = 0;
if(debugging) Serial.print("Menu state: ");
if(debugging) Serial.println(menu_state);
}

