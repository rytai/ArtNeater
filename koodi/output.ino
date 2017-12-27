void lcdFlush()
{
  lcd.setCursor(0, 1);
  lcd.print("                  ");
}

void UpdateLCD()
{
  lcdFlush();
  lcd.setCursor(0, 1);
  lcd.print(menu_lcd_projection);
}

void colormix(){

  
}

