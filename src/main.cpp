#include "ps2dev.h"    //Emulate a PS/2 device
PS2dev keyboard(3,2);  //clock, data

unsigned long timecount = 0;
uint8_t serialData[2];

void setup()
{
  keyboard.keyboard_init();
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  //Handle PS2 communication and react to keyboard led change
  //This should be done at least once each 10ms
  unsigned char leds;
  if(keyboard.keyboard_handle(&leds)) {
    //Serial.print('LEDS');
    //Serial.print(leds, HEX);
    digitalWrite(LED_BUILTIN, leds);
  }

  if (Serial.available){
    Serial.readBytes(serialData,2);
    if (serialData[0]){
      keyboard.keyboard_mk(serialData[1]);
    }
    else{
      keyboard.keyboard_brk(serialData[1]);
    }
  }
}