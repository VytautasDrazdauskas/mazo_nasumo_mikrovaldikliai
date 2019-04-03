/*
 watchdog timer basic
 1. su oscilografu reikia ismatuoti impulso tikra trukme kai norm ir kai pasildytas procas. Pagal Atmega 328p 47psl apskaiciuoti realu WDT oscilatoriaus dazni. kai 0.5s 498ms kai 8s -7.98s -Funduino 
                                                                                                                                                       0.5s 551ms - Arduino (irgi paskaiciuot)

Funduino atvejis: 498 / 65536 =0,007598876953125 ms = 0,000007598876953125s
T =  0,000007598876953125 s
f = 1 / T = 1 / 0,000007598876953125 = 131598,39357429718875502008032129 Hz 

 (498*65536)/500=65273,856ms <-- normavimas. Reikes ataskaitoj.
 
2. parasyti koda i loopa ir apkrauti arduina taip, kad WDT suveiktu ir indikuotu su diodu veikima. (programiskai uzlausti)
*/

#include <avr/wdt.h>

char rip[1023];
boolean kint = false;

void setup(){
  pinMode(13,OUTPUT);
  cli();
  wdt_reset();

  WDTCSR|=(1<<WDCE)|(1<<WDE);
  WDTCSR=(1<<WDIE)|(1<<WDE)|(0<<WDP3)|(1<<WDP2)|(0<WDP1)|(1<<WDP0); 
  sei();
  //Serial.
}

void loop()
{
  //lauziam WDT (Arduino)
  wdt_reset();
  //delay(400); //WDT neveikia
  //delay(500); //WDT neveikia
  //delay(600); //WDT veikia
  delay(551); //WDT neveikia
  //delay(560); //WDT veikia
  //delay(555); //WDT veikia
  //delay(551); //WDT veikia
}

ISR(WDT_vect)
{
  WDTCSR=(1<<WDIE);
  kint=!kint;
  digitalWrite(13,kint);
  
}
