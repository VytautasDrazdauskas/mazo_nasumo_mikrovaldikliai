#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#define RL A1
#define GL 2
#define ZLED 3

#define M1 4
#define M2 5

RF24 radio(7,6);

const uint64_t pipe1 = 0xE8E8F0F0E1LL;
const uint64_t pipe2 = 0xE8E8F0F0E2LL;

byte led[]={
  RL,GL,ZLED};
char data[32];
int c;

void setup() {
  pinMode(RL,1);
  pinMode(GL,1);
  pinMode(ZLED,1);
  pinMode(M1,INPUT_PULLUP);
  pinMode(M2,INPUT_PULLUP);
  Serial.begin(9600);

  radio.begin();
  radio.setRetries(15,15);
  
  radio.setChannel(100);
  radio.setAutoAck(0);  //isjungiu autoACK
  
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.setPayloadSize(2);
  radio.openWritingPipe(pipe1);
  radio.openReadingPipe(1,pipe1);
  radio.startListening();
}

void loop() {
  if(Serial.available()){
    c=Serial.read();
    radio.stopListening();
    delay(10);
    bool ok = radio.write( &c, 2);
    //if(ok) Serial.println("nusiunciau");
    radio.startListening();
  }

  if ( radio.available() ){
    delay(10);
    radio.read(&c, 2);
    Serial.println(char(c));
  }  
}
void ledOn(byte i){
  digitalWrite(led[i],1);
  delay(200);
}
void ledOff(byte i){
  digitalWrite(led[i],0);
  delay(200);
}

