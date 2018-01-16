//Päivitä encoderin sijainti ja palauta onko se muuttunut
bool InputEncoderHasChanged(){
  //Serial.print("Encoder change");
  encoder_clk_last = encoder_clk_current;
  encoder_clk_current = digitalRead(PIN_ENCODER_CLK);
  //Pyörähdys lasketaan vain encoderin clk pinnin laskureunalla.
  if ( (encoder_clk_current != encoder_clk_last) && !encoder_clk_current){
    //clk muuttui ensin -> pyörähdettiin myötäpäivään
    if( digitalRead(PIN_ENCODER_DT) != encoder_clk_current ){
     // encoder_movement_last = encoder_movement;
      encoder_movement += 1;   
    }else{ // Pyörähdettiin vastapäivään
    //  encoder_movement_last = encoder_movement;
      encoder_movement -= 1;
    }
    Serial.println(encoder_movement);
      return true;
  }else{
      return false;
  }
}

bool InputButtonHasChanged(){
  button_pressed_last = button_pressed_current;
  button_pressed_current = digitalRead(PIN_ENCODER_BUTTON);
  /*
  Serial.print ("BUTTON Current: ");
  Serial.print (button_pressed_last);
  Serial.print (" BUTTON Last: ");
  Serial.print (button_pressed_current);
  Serial.print (" ##");
  Serial.print (digitalRead(PIN_ENCODER_BUTTON));
  Serial.println (" ##");
  */
  if (button_pressed_current != button_pressed_last){
    if(!button_pressed_current){
      button_falling_edge = true;
    }
    button_falling_edge = false;
    return true;
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
  if ( InputButtonHasChanged() ){
    input_changed = true;
    selection=!selection;
    Serial.println("SELECTION CHANGE!!!!!!!!!!!!!!!!!!!!!!!!!!!");
  
  }
  return input_changed;
}

//Tähän tulee encoderin kiihtyvyyden käsittely
//Menu luokassa kutsutaan tätä
signed int GetEncoderMovement(){
  return encoder_movement;
}
