#include "output.h"

void UpdateLCD()
{
if () //menu level
{
	if (encoderPosCount == )// dmx channel select
	{
		lcd.setCursor(0, 1);
		lcd.print("DMX channel:      ");
		lcd.setCursor(0, 1);
		lcd.print("DMX channel: ");
		lcd.print(DMXchannel);

	}
	else if ()// dmx channel count
	{
		lcd.setCursor(0, 1);
		lcd.print("DMX channel count:      ");
		lcd.setCursor(0, 1);
		lcd.print("DMX channel count: ");
		lcd.print(DMXchcount);
	}
	else if () //mode individual channels/all in one
	{
		lcd.setCursor(0, 1);
		lcd.print("Mode:      ");
		lcd.setCursor(0, 1);
		lcd.print("Mode ");
	}
	else if () //max brightness
	{
		lcd.setCursor(0, 1);
		//1234567890123456
		lcd.print("LED brightness:      ");
		lcd.setCursor(0, 1);
		lcd.print("LED MAX brightness: ");
		lcd.print(brightness);
	}
	else if () //manual colormix/demo macro parameters
	{

	}
	else if () //Demo macro on/off
	{

	}
	else if ()// Wifi
	{
		lcd.setCursor(0, 1);
		lcd.print("IP-address                    ");
		lcd.setCursor(0, 1);
		lcd.print("IP-address: ");
		lcd.print(IPaddress);
	}
}
	else if () //parameters selection
	{

	}
}


