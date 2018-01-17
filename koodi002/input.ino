//Päivitä encoderin sijainti ja palauta onko se muuttunut
bool InputEncoderHasChanged(){
  int maxMillisecondsBetweenTicks;
  //Serial.print("Encoder change");
  encoder_clk_last = encoder_clk_current;
  encoder_clk_current = digitalRead(PIN_ENCODER_CLK);
  //Pyörähdys lasketaan vain encoderin clk pinnin laskureunalla.
  if ( (encoder_clk_current != encoder_clk_last) && !encoder_clk_current){
    //clk muuttui ensin -> pyörähdettiin myötäpäivään

    unsigned long c_time = millis();

    if(c_time > (lastTickMillis + 2)){
      
    if( digitalRead(PIN_ENCODER_DT) != encoder_clk_current ){
     // encoder_movement_last = encoder_movement;      
      if(c_time < (lastTickMillis + maxMillisecondsBetweenTicks)){        
        ticks ++;
      }else {
        ticks = 1;
      }    
      lastTickMillis = c_time;
      
    }else{ // Pyörähdettiin vastapäivään
    //  encoder_movement_last = encoder_movement;
      if(c_time < (lastTickMillis + maxMillisecondsBetweenTicks)){        
        ticks --;
      }else {
        ticks = -1;
      }
    
      lastTickMillis = c_time;
    }
    encoder_movement += ticks;
    
    if(debugging) Serial.println(encoder_movement);
      return true;
    }
    
  }else{
      return false;
  }
}

bool InputButtonLowEdge(){
  
  button_pressed_last = button_pressed_current;
  button_pressed_current = digitalRead(PIN_ENCODER_BUTTON);

  
  if ((button_pressed_current != button_pressed_last)&&!button_pressed_current){
    unsigned long c_time = millis();
    if(c_time > (buttonLastMillis + buttonDeBounceInterval)){  
      buttonLastMillis = millis();
      if (debugging) Serial.println ("Button low edge");
      return true;
    }else{
      return false;
    }
  }
  return false;
}

//Päivitetään input laitteiden tila
//palauttaa true, jos jotain on muuttunut.
bool UpdateInput(){
  bool input_changed = false; //Palautetaan funktion lopussa true jos jokin muuttunut
  if ( InputEncoderHasChanged() ){
    input_changed = true;
  }
  if ( InputButtonLowEdge() ){
    input_changed = true;
    if(debugging) Serial.print("SELECTION CHANGE:");
    if(debugging) Serial.println(selection);
    selection = !selection;
    if(selection){
      menu_lcd_projection[15] = '#';
    }else{
      menu_lcd_projection[15] = ' ';
    }

  }
  return input_changed;
}

//Tähän tulee encoderin kiihtyvyyden käsittely
//Menu luokassa kutsutaan tätä
signed int GetEncoderMovement(){
  return encoder_movement;
}
