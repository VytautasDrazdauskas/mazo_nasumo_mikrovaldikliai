const byte ledPin = 13;
const byte interruptPin = 2;
const byte interruptReset = 3;
volatile byte state = LOW;
volatile int number = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  pinMode(interruptPin, INPUT_PULLUP);
  pinMode(interruptReset, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, FALLING);
  attachInterrupt(digitalPinToInterrupt(interruptReset), reset, RISING);
}

void loop() {
  digitalWrite(ledPin, state);
  Serial.println(number);
  //number = 0;
  delay(30);
}

void blink() {      
 static unsigned long last_interrupt_time = 0;
 unsigned long interrupt_time = millis();
 
 if (interrupt_time - last_interrupt_time > 200)
 {
   state = !state;
   number++; 
 }
 last_interrupt_time = interrupt_time;
  
}

void reset(){
  number = 0; 
}
