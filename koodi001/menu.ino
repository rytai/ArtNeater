void menuLCD(){
  //DMX address
  if(menu_state==0){
                      //1234567890123456
  menu_lcd_projection="Channel start    "
                      "> "+ channel_start+ "\0";  
  }
  //LED count
  else if(menu_state==1){
                     //1234567890123456
  menu_lcd_projection="Channel width   "
                        + channel_width;
                        
  }
  //Operation mode
  else if(menu_state==2){
    if(operation_mode==0)
    {
                      //1234567890123456
  menu_lcd_projection="Mode: ARTnet"+ "\0";  
    }
    else if(operation_mode==1)
    {
 menu_lcd_projection="Mode: manual color"+ "\0";      
    }
    else if(operation_mode==2)
    {
 menu_lcd_projection="Mode: demo"+ "\0";      
    }
  }
  //Max brightness
  else if(menu_state==3){
 if(brightness<25)
    {
                    //1234567890123456
 menu_lcd_projection="Brightness: "+brightness
                     "X"+ "\0";      
    }  
 else if(brightness>=25 && brightness<50)
    {
                    //1234567890123456
 menu_lcd_projection="Brightness: "+brightness
                     "XX"+ "\0";      
    }
     else if(brightness>=50 && brightness<75)
    {
                    //1234567890123456
 menu_lcd_projection="Brightness: "+brightness
                     "XXX"+ "\0";      
    }
     else if(brightness>=75 && brightness<100)
    {
                    //1234567890123456
 menu_lcd_projection="Brightness: "+brightness
                     "XXXX"+ "\0";      
    }
     else if(brightness>=100 && brightness<125)
    {
                    //1234567890123456
 menu_lcd_projection="Brightness: "+brightness
                     "XXXXX"+ "\0";      
    }
     else if(brightness>=125 && brightness<150)
    {
                    //1234567890123456
 menu_lcd_projection="Brightness: "+brightness
                     "XXXXXX"+ "\0";      
    }
     else if(brightness>=150 && brightness<175)
    {
                    //1234567890123456
 menu_lcd_projection="Brightness: "+brightness
                     "XXXXXXX"+ "\0";      
    }
     else if(brightness>=200 && brightness<225)
    {
                    //1234567890123456
 menu_lcd_projection="Brightness: "+brightness
                     "XXXXXXXX"+ "\0";      
    }
     else if(brightness>=225 && brightness<255)
    {
                    //1234567890123456
 menu_lcd_projection="Brightness: "+brightness
                     "XXXXXXXXX"+ "\0";      
    }
  }
  //manual red
  else if(menu_state==4){
  menu_lcd_projection="Red level: "+int(simpleRGB_r) + "\0";  
  }
  //manual blue
  else if(menu_state==5){
  menu_lcd_projection="Blue level: "+int(simpleRGB_b) + "\0";  
  }
  //manual green
  else if(menu_state==6){
  menu_lcd_projection="Green level "+int(simpleRGB_g) + "\0";  
  }
  //demo macro (placeholder)
  else if(menu_state==7){
  menu_lcd_projection="Demo"+ "\0";  
  }
  //Wifi state and IP address (placeholder)
  else if(menu_state==8){
  menu_lcd_projection="Wifi: "+ "\0";  
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

