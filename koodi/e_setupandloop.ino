

//LCD


//#include "definitions.h" //Pin definition
//#include "input.h" //Encoderin syötteet
//#include "output.h" //30.11. lcdnäytön tulosteet





void setup() { 
    //Alustetaan GPIO pinnit
    pinMode (PIN_ENCODER_CLK,INPUT);
    pinMode (PIN_ENCODER_DT,INPUT);
  pinMode (PIN_ENCODER_BUTTON,INPUT);
  pinMode (PIN_LCD_SDA,OUTPUT);
  pinMode (PIN_LCD_SCL,OUTPUT);

    //Alustetaan laitteisiin liittyvät muuttujat
    encoder_dt_last = digitalRead(PIN_ENCODER_DT);

    //Aloitetaan serial debugging
    Serial.begin (9600);
    Serial.println("Starting.");

  //alustetaan lcd-näyttö
  int status;
  status = lcd.begin(LCD_COLS, LCD_ROWS);
  if (status) // non zero status means it was unsuccesful
  {
    status = -status; // convert negative status value to positive number

    // begin() failed so blink error code using the onboard LED if possible
    hd44780::fatalError(status); // does not return
  }

  // initialization was successful, the backlight should be on now

  // Print a message to the LCD
  lcd.print("Hello, World!");

    //Alustetaan ajanotot
    lcd_update_next = millis();
    mainloop_next_update = millis();
}

//Sisältää menutoiminnot
//Palauttaa true, jos menu on muuttunut -> seuraa lcd päivitys
bool UpdateMenu(){
    return true;
}

//void UpdateLCD(){} moved to c_output

void loop() {
    //Testataan onko kulunut tarpeeksi aikaa viimeisestä loopin läpikäynnistä
    current_time = millis();
    if (current_time >= mainloop_next_update){
        mainloop_next_update = current_time + mainloop_max_frequency;

        //Testataan syöttölaitteet ja kutsutaan menun päivitystä jos jokin syöte on muuttunut
        if ( UpdateInput() ){
            //jos menu muuttunut -> Merkataan lcd näyttö päivitettäväksi
            display_update_required = UpdateMenu();
        }
        //jos tarpeeksi aikaa on kulunut viime lcd päivityksestä -> päivitetään lcd
        if ( display_update_required && (millis() >= lcd_update_next) ){
            lcd_update_next += lcd_update_frequency;
            UpdateLCD();
        }
    }
} 
