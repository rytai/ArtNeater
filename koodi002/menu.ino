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
  const int valuePosition = 17;
  char valueAsChar[3];  
  //"Tulostaa" numeron char arrayhyn
  sprintf(valueAsChar, "%d", val);
  Serial.println("testi"); 
  for(int i = 0; i < 3; i++){
    menu_lcd_projection[i+valuePosition] = ' ';
    menu_lcd_projection[i+valuePosition] = valueAsChar[i];
    Serial.print("Val as char ");
    Serial.println(valueAsChar[i]);
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
  Serial.print("Menu: ");
  Serial.println(selection);
  if(selection){
    if(menu_state==0){
      encoder_movement += encoder_movement - encoder_movement_last;
    }
    else if(menu_state==1){
      channel_width+= encoder_movement - encoder_movement_last;
    }
    else if(menu_state==2){
      operation_mode+= encoder_movement - encoder_movement_last;
    }
    else if(menu_state==3){
      brightness+= encoder_movement - encoder_movement_last;
    }
    else if(menu_state==4){
      simpleRGB_change = true;
      simpleRGB_r+= encoder_movement - encoder_movement_last;
    }
    else if(menu_state==5){
      simpleRGB_change = true;
      simpleRGB_b+= encoder_movement - encoder_movement_last;
    }
    else if(menu_state==6){
      simpleRGB_change = true;
      simpleRGB_g+= encoder_movement;
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
menu_state += encoder_movement;
/*if(encoder_movement>encoder_movement_last) menu_state++;
else if(encoder_movement<encoder_movement_last) menu_state--;
*/
encoder_movement = 0;
Serial.print("Menu state: ");
Serial.println(menu_state);
}

