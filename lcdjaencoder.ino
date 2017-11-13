
#include <Wire.h> //I2C kommunikointi
#include <hd44780.h>//hd44780 ajuri
#include <hd44780ioClass/hd44780_I2Cexp.h> //i2c expander ajuri lcd:lle

//############################## LCD ############################## 

// LCD koko
const int LCD_COLS = 16;
const int LCD_ROWS = 2;

//############################ ENCODER ############################ 
int pinEncCLK = 14;  // clk pinni
int pinEncDT  = 12;  // suunta pinni
int encoderPosCount = 0; //encoder sijainti
int pinALast;
int aVal;
boolean bCW;

signed int momentum = 0;
unsigned long momentumUpdate = 0;
unsigned long momentumUpdateFreq = 200; //ms

hd44780_I2Cexp lcd; // declare lcd object: auto locate & config exapander chip

void setup() {
  pinMode (pinA, INPUT);
  pinMode (pinB, INPUT);
  /* Read Pin A
    Whatever state it's in will reflect the last position
  */
  pinALast = digitalRead(pinA);
  Serial.begin (9600);

  int status;
  status = lcd.begin(LCD_COLS, LCD_ROWS);
  if (status) // non zero status means it was unsuccesful
  {
    status = -status; // convert negative status value to positive number

    // begin() failed so blink error code using the onboard LED if possible
    hd44780::fatalError(status); // does not return
  }

  // initalization was successful, the backlight should be on now

  // Print a message to the LCD
  lcd.print("Hello, World!");
}

void loop() {
  aVal = digitalRead(pinA);

  if (millis() >= momentumUpdate) {
    momentumUpdate = momentumUpdate + momentumUpdateFreq;
    Serial.println("-------------------");
    if (momentum < 0) {
      momentum ++;
    } else if (momentum > 0) {
      momentum --;
    }
    Serial.println(momentum);
    Serial.println("-------------------");
  }

  if (aVal != pinALast && !aVal) { // Means the knob is rotating
    // if the knob is rotating, we need to determine direction
    // We do that by reading pin B.
    if (digitalRead(pinB) != aVal) {  // Means pin A Changed first - We're Rotating Clockwise
      momentum = momentum + 1;
      encoderPosCount = encoderPosCount + momentum;
      bCW = true;
    } else {// Otherwise B changed first and we're moving CCW
      bCW = false;
      momentum = momentum - 1;
      encoderPosCount = encoderPosCount + momentum;
    }
    Serial.print ("Rotated: ");
    if (bCW) {
      Serial.println ("clockwise");
    } else {
      Serial.println("counterclockwise");
    }
    lcd.setCursor(0, 1);
    lcd.print("EncoderPos:     ");
    lcd.setCursor(0, 1);
    lcd.print("EncoderPos: ");
    lcd.print(encoderPosCount);
    Serial.print("Encoder Position: ");
    Serial.println(encoderPosCount);
  }
  pinALast = aVal;
}
