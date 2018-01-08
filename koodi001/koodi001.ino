#include "definitions.h" //Pin definition


void setup() { 

  //Aloitetaan serial debugging
  Serial.begin (9600);
  Serial.println("Starting.");
  
    //Alustetaan GPIO pinnit
  pinMode (PIN_ENCODER_CLK,INPUT);
  pinMode (PIN_ENCODER_DT,INPUT);
  pinMode (PIN_ENCODER_BUTTON,INPUT);
  /*
  pinMode (PIN_LCD_SDA,OUTPUT);
  pinMode (PIN_LCD_SCL,OUTPUT);
  */


  //Alustetaan laitteisiin liittyvät muuttujat
  encoder_dt_last = 0;
  
  Serial.println("test");


  //alustetaan lcd-näyttö
  int status_;
 /* status_ = lcd.begin(LCD_COLS, LCD_ROWS);
  if (status_) // non zero status means it was unsuccesful
  {
    Serial.print("LCD not connected. hanging program up");
    status_ = -status_; // convert negative status value to positive number

    // begin() failed so blink error code using the onboard LED if possible
    hd44780::fatalError(status_); // does not return
  }

  // initialization was successful, the backlight should be on now
  Serial.print("LCD connected.");
  // Print a message to the LCD
  lcd.print("Hello, World!");
*/
    //Alustetaan ajanotot
    os_timer_setfn(&interrupt_timer,timerISR,NULL);
    os_timer_arm(&interrupt_timer,interrupt_frequency,true);
    lcd_update_next = millis();
    mainloop_next_update = 0;
}

//Sisältää menutoiminnot
//Palauttaa true, jos menu on muuttunut -> seuraa lcd päivitys
//bool UpdateMenu moved to menu.ino

//void UpdateLCD(){} moved to c_output

void loop() {
    //Testataan onko kulunut tarpeeksi aikaa viimeisestä loopin läpikäynnistä
    current_time = millis();
     if(interrupt_test=true){
      Serial.println("interrupt");
      interrupt_test=false;
    }
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
