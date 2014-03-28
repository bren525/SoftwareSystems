/*
  

 Author: Allen Downey 
 
 Based on http://arduino.cc/en/Tutorial/AnalogInput
 Created by David Cuartielles
 modified 30 Aug 2011
 By Tom Igoe

 License: Public Domain
 
 */
  
int ledPin = 5;       // select the pin for the LED
int buttonPin1 = 2;
int buttonPin2 = 3;

void setup() {
  Serial.begin(9600);

  DDRD = B11100000;
  pinMode(buttonPin1, INPUT_PULLUP);  
  pinMode(buttonPin2, INPUT_PULLUP);  
  DDRB = B00111111;
  
  cli();//stop interrupts
  
  
  //set timer2 interrupt at 8kHz
  TCCR2A = 0;// set entire TCCR2A register to 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2  = 0;//initialize counter value to 0
  // set compare match register for 8khz increments
  OCR2A = 249;// = (16*10^6) / (8000*8) - 1 (must be <256)
  // turn on CTC mode
  TCCR2A |= (1 << WGM21);
  // Set CS21 bit for 8 prescaler
  TCCR2B |= (1 << CS21);   
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);
  
  
  //set timer0 interrupt at 2kHz
  TCCR0A = 0;// set entire TCCR2A register to 0
  TCCR0B = 0;// same for TCCR2B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 2khz increments
  OCR0A = 124;// = (16*10^6) / (2000*64) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR0B |= (1 << CS01) | (1 << CS00);   
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);
  
  
  sei();//allow interrupts
  
  attachInterrupt(1,togglePitch,FALLING);
  
}

void writeByte(int x) {

  PORTB |= x>>2;
  PORTB &= (x>>2 | B11000000);
  PORTD |= x<<6;
  PORTB &= (x<<6 | B00111111); //Only sets pins 6...13
  //Bits flipped manually on board
  

}

int low = 36;
int high = 255;
int stride1 = 5;
int stride2 = 10;
int counter = low;

ISR(TIMER2_COMPA_vect){
  
  int button1 = digitalRead(buttonPin1);
  if (button1) return;
  
  
  counter += stride1;
  if (counter > high) {
    counter = low;
    
  }
 
  writeByte(counter);
}

ISR(TIMER0_COMPA_vect){
  int button1 = digitalRead(buttonPin1);
  if (button1) return;
  
  
  counter += stride2;
  if (counter > high) {
    counter = low;
    
  }

  writeByte(counter);
}

void togglePitch(){
  stride1 *= 2;
  stride2 *= 2;
  if(stride1 >=50){
    stride1 = 5;
    stride2 = 10;
    
  }
}

void loop() {
}
