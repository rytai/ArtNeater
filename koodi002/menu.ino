//Kaikkien tulee olla saman pituisia.
const int headerLenght = 11;
const char hBrightness[] = "Brightness:";
const char hHeader2[]    = "Jokumuu:   ";
const char hHeader14[]   = "vieläyksi: ";

//Siirtää headerLenght määrän kirjaimia annetusta arraysta menu_lcd_projection arrayyn.
void putHeader(char * headerText){
  for(int i = 0; i < headerLenght; i++){
    menu_lcd_projection[i] = headerText[i];
  }
}

//Muuntaa annetun tavun char-arvoksi ja vie sen arrayyn.
void putValue(int val){
  const int valuePosition = 13;
  char valueAsChar[3];  
  //"Tulostaa" numeron char arrayhyn
  sprintf(valueAsChar, "%d", val); 
  for(int i = 0; i < 3; i++){
    menu_lcd_projection[i+valuePosition] = valueAsChar[i];
  }
}


void menuLCD(){
  /*
  //DMX address
  if(menu_state==0){
                      //1234567890123456
  menu_lcd_projection="Channel start   
                       > "+ channel_start;  
  }
  //LED count
  else if(menu_state==1){
                     //1234567890123456
  menu_lcd_projection="Channel width   
                       > "+ channel_width;
                        
  }
  //Operation mode
  else if(menu_state==2){
    if(operation_mode==0)
    {
                      //1234567890123456
  menu_lcd_projection="Mode: ARTnet";  
    }
    else if(operation_mode==1)
    {
 menu_lcd_projection="Mode: manual color";      
    }
    else if(operation_mode==2)
    {
 menu_lcd_projection="Mode: demo";      
    }
  }
  //Max brightness
  else if(menu_state==3){
 if(brightness<25)
    {
                    //1234567890123456
 menu_lcd_projection="Brightness: "+brightness
                     "X";      
    }  
 else if(brightness>=25 && brightness<50)
    {
                    //1234567890123456
 menu_lcd_projection="Brightness: "+brightness
                     "XX";      
    }
     else if(brightness>=50 && brightness<75)
    {
                    //1234567890123456
 menu_lcd_projection="Brightness: "+brightness
                     "XXX";      
    }
     else if(brightness>=75 && brightness<100)
    {
                    //1234567890123456
 menu_lcd_projection="Brightness: "+brightness
                     "XXXX";      
    }
     else if(brightness>=100 && brightness<125)
    {
                    //1234567890123456
 menu_lcd_projection="Brightness: "+brightness
                     "XXXXX";      
    }
     else if(brightness>=125 && brightness<150)
    {
                    //1234567890123456
 menu_lcd_projection="Brightness: "+brightness
                     "XXXXXX";      
    }
     else if(brightness>=150 && brightness<175)
    {
                    //1234567890123456
 menu_lcd_projection="Brightness: "+brightness
                     "XXXXXXX";      
    }
     else if(brightness>=200 && brightness<225)
    {
                    //1234567890123456
 menu_lcd_projection="Brightness: "+brightness
                     "XXXXXXXX";      
    }
     else if(brightness>=225 && brightness<255)
    {
                    //1234567890123456
 menu_lcd_projection="Brightness: "+brightness
                     "XXXXXXXXX";      
    }
  }
  //manual red
  else if(menu_state==4){
  menu_lcd_projection="Red level: "+simpleRGB_r;  
  }
  //manual blue
  else if(menu_state==5){
  menu_lcd_projection="Blue level: "+simpleRGB_b;  
  }
  //manual green
  else if(menu_state==6){
  menu_lcd_projection="Green level "+simpleRGB_g;  
  }
  //demo macro (placeholder)
  else if(menu_state==7){
  menu_lcd_projection="Demo";  
  }
  //Wifi state and IP address (placeholder)
  else if(menu_state==8){
  menu_lcd_projection="Wifi: ";  
  }
  */
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

