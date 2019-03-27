
//address will look like http://192.168.1.102
#define RLED A1
#define GLED 2
#define ZLED 3

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xDD }; //Nepamirštame pasikeisti adreso pagal darbo vietos numerį
byte ip[] = {10, 204, 0, 202 };                    //Taip pat keičiame pagal darbo vietos numerį


//byte gateway[] = {192, 168, 1, 1 }; // internet access via router
byte subnet[] = {255, 255, 255, 0 }; //subnet mask
EthernetServer server(80); //server port arduino server will use
EthernetClient client;

String readString; //used by server to capture GET request 

void setup(){
  pinMode(RLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(ZLED, OUTPUT);
  // Ethernet.begin(mac,ip,gateway,gateway,subnet); 
  Ethernet.begin(mac,ip,subnet); 
  server.begin();
  Serial.begin(9600); 
}

void loop(){
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        //read char by char HTTP request
        if (readString.length() < 100) {

          //store characters to string 
          readString += c; 
          //Serial.print(c);
        } 

        //if HTTP request has ended
        if (c == '\n') {

          ///////////////
          Serial.print(readString); //print to serial monitor for debuging 

            //now output HTML data header
          if(readString.indexOf('?') >=0) { //don't send new page
            client.println(F("HTTP/1.1 204"));
            client.println();
            client.println();  
          }
          else {   
            client.println(F("HTTP/1.1 200 OK")); //send new page on browser request
            client.println(F("Content-Type: text/html"));
            client.println();

            client.println(F("<HTML>"));
            client.println(F("<HEAD>"));
            client.println(F("<TITLE>WEB LED CONTROL</TITLE>"));
            client.println(F("</HEAD>"));
            client.println(F("<BODY>"));

            // DIY buttons. Raudono LED valdymas
            client.println(F("Raudona"));
            client.println(F("<a href=/?on2 target=inlineframe>ON</a>")); 
            client.println(F("<a href=/?off3 target=inlineframe>OFF</a><br><br>"));
            
            //------------  Vieta jūsų žalio ir geltono led valdymui
            client.println(F("Geltonas ledas"));
            client.println(F("<a href=/?on4 target=inlineframe>ON</a>"))
            ;client.println(F("<a href=/?off5 target=inlineframe>OFF</a><br><br>"));
            
            client.println(F("Zalias ledas"));
            client.println(F("<a href=/?on6 target=inlineframe>ON</a>"));
            client.println(F("<a href=/?off7 target=inlineframe>OFF</a><br><br>"));
            //--------------     
            client.println(F("Pins"));
            client.println(F("&nbsp;<a href=/?off2468 target=inlineframe>ALL ON</a>")); 
            client.println(F("&nbsp;<a href=/?off3579 target=inlineframe>ALL OFF</a>")); 
            client.println(F("<IFRAME name=inlineframe style='display:none'>"));          
            client.println(F("</IFRAME>"));
            client.println(F("</BODY>"));
            client.println(F("</HTML>"));
          }
          delay(1);
          //stopping client
          client.stop();

          ///////////////////// control arduino pin
          if(readString.indexOf('2') >0)
          {
            digitalWrite(RLED, HIGH);
            Serial.println(F("Led Raudona On"));
            Serial.println();
          }
          if(readString.indexOf('3') >0)
          {
            digitalWrite(RLED, LOW);
            Serial.println(F("Led Raudona Off"));
            Serial.println();
          } 
          //--------------- įdedame kodo LED valdymui
            
            if(readString.indexOf('4') >0){
              digitalWrite(GLED,HIGH);
              Serial.println(F("Led Geltona On"));
              Serial.println();
            }
            if(readString.indexOf('5') >0){
              digitalWrite(GLED,LOW);
              Serial.println(F("Led Geltona Off"));
              Serial.println();
            }
            if(readString.indexOf('6') >0){
              digitalWrite(ZLED,HIGH);
              Serial.println(F("Led Zalia On"));
              Serial.println();
            }
            if(readString.indexOf('7') >0){
              digitalWrite(ZLED,LOW);
              Serial.println(F("Led Zalia Off"));
              Serial.println();
            }


          //---------------
          readString="";
        }
      }
    }
  }
} 
