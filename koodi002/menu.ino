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
void putHeader(char * headerText){
  for(int i = 0; i < headerLenght; i++){
    menu_lcd_projection[i] = headerText[i];
  }
}

//Muuntaa annetun tavun char-arvoksi ja vie sen arrayyn.
void putValue(int val){
  const int valuePosition = 17;
  char valueAsChar[3];  
  //"Tulostaa" numeron char arrayhyn
  sprintf(valueAsChar, "%d", val); 
  for(int i = 0; i < 3; i++){
    menu_lcd_projection[i+valuePosition] = valueAsChar[i];
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
  putValue(channel_count);
                        
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
  putValue(simple_RGB_r);
  }
  //manual blue
  else if(menu_state==5){
  putHeader(hManualB);
  putValue(simple_RGB_b);  
  }
  //manual green
  else if(menu_state==6){
  putHeader(hManualG);
  putValue(simple_RGB_g);
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
  if(menu_state==0){
    if(selection){
      if(encoder_movement>encoder_movement_last) channel_start++;
      else if(encoder_movement<encoder_movement_last) channel_start--;
    }
    else menuSwitch();
  }
  else if(menu_state==1){
    if(selection){
      if(encoder_movement>encoder_movement_last) channel_width++;
      else if(encoder_movement<encoder_movement_last) channel_width--;
    }
    else menuSwitch();
  }
  else if(menu_state==2){
    if(selection){
      if(encoder_movement>encoder_movement_last) operation_mode++;
      else if(encoder_movement<encoder_movement_last) operation_mode--;
    }
    else menuSwitch();
  }
  else if(menu_state==3){
    if(selection){
      if(encoder_movement>encoder_movement_last) brightness++;
      else if(encoder_movement<encoder_movement_last) brightness--;
    }
    else menuSwitch();
  }
  else if(menu_state==4){
    if(selection){
      if(encoder_movement>encoder_movement_last) simpleRGB_r++;
      else if(encoder_movement<encoder_movement_last) simpleRGB_r--;
    }
    else menuSwitch();
  }
  else if(menu_state==5){
    if(selection){
      if(encoder_movement>encoder_movement_last) simpleRGB_b++;
      else if(encoder_movement<encoder_movement_last) simpleRGB_b--;
    }
    else menuSwitch();
  }
  else if(menu_state==6){
    if(selection){
      if(encoder_movement>encoder_movement_last) simpleRGB_g++;
      else if(encoder_movement<encoder_movement_last) simpleRGB_g--;
    }
    else menuSwitch();
  }
  else if(menu_state==7){
    if(selection){

    }
    else menuSwitch();
    
  }
  else if(menu_state==8){
    if(selection){
      
    }
    else menuSwitch();
    
  }
  menuLCD();
    return true;
}

void menuSwitch(){
if(encoder_movement>encoder_movement_last) menu_state++;
else if(encoder_movement<encoder_movement_last) menu_state--;
}

