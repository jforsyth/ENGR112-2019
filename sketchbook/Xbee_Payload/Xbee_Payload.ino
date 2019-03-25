/*****************************************************************
  XBee_Serial_Passthrough.ino

  Set up a software serial port to pass data between an XBee Shield
  and the serial monitor.

  Hardware Hookup:
  The XBee Shield makes all of the connections you'll need
  between Arduino and XBee. If you have the shield make
  sure the SWITCH IS IN THE "DLINE" POSITION. That will connect
  the XBee's DOUT and DIN pins to Arduino pins 2 and 3.


  Software from SparkFun (c) 2019. Used from https://learn.sparkfun.com/tutorials/xbee-shield-hookup-guide
*****************************************************************/
// We'll use SoftwareSerial to communicate with the XBee:
#include <SoftwareSerial.h>

//For Atmega328P's
// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
SoftwareSerial XBee(2, 3); // RX, TX

void setup()
{
  // Set up both ports at 9600 baud. This value is most important
  // for the XBee. Make sure the baud rate matches the config
  // setting of your XBee.
  XBee.begin(9600);
  Serial.begin(9600);

  Serial.println("\n***Begin Xbee Program***");
  Serial.println("Any characters send via the serial terminal");
  Serial.println("will be transmitted to the base station.");
  Serial.println("Any data received from the station will be printed here.\n\n\n");
}

void loop()
{

  //If any data comes in from the terminal, send it to the Basestation
  if (Serial.available())
  {
    while (Serial.available())
    {
      char c = Serial.read();
      Serial.print(c);
      XBee.write(c);
    }
  }

  //Data received from the Basestation, bring to our serial terminal.
  if (XBee.available())
  {
    while (XBee.available())
    {
      char c = XBee.read();
      Serial.write(c);
    }
  }
}

