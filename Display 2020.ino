#include <TimerOne.h>
#include <EEPROM.h>

#define NDIGITS         8
#define NDIGITS_MASK    7

const int latchpin = 12 ;       // connect to RCK
const int clockpin = 11 ;       // connect to SCK
const int datapin = 10 ;        // connect to DIO

unsigned long previousTime = 0;
byte seconds = 0;
byte minutes = 0;
byte hours = 0;

byte col[NDIGITS] = {
    0b00000001,     //1
    0b00000010,     //2
    0b00000100,     //4
    0b00001000,     //8
    0b00010000,     //16
    0b00100000,     //32
    0b01000000,     //64
    0b10000000      //128
} ;

byte seg[] = {
    0b11000000,     // 0
    0b11111001,     // 1
    0b10100100,     // 2
    0b10110000,     // 3
    0b10011001,     // 4
    0b10010010,     // 5
    0b10000010,     // 6
    0b11111000,     // 7
    0b10000000,     // 8
    0b10010000,     // 9  
} ;     

byte segbuf[NDIGITS] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
byte segcnt = 0;

#define USE_DIRECT_PORT_ACCESS  
#ifndef USE_DIRECT_PORT_ACCESS

void LED_irq(void)
{
    digitalWrite(latchpin, LOW);
    // select the digit...
    shiftOut(datapin, clockpin, MSBFIRST, col[segcnt]) ;
    // and select the segments
    shiftOut(datapin, clockpin, MSBFIRST, segbuf[segcnt]) ;
    digitalWrite(latchpin, HIGH) ;
    segcnt ++ ;
    segcnt &= NDIGITS_MASK ;
}
#else

void LED_irq(void)
{
    PORTB &= ~0b00010000 ;
   
  for (int i=0; i<8; i++) 
  {
  if (col[segcnt] & (0x80 >> i))
  PORTB |= 0b00000100 ;
  else
  PORTB &= ~0b00000100 ;
  PORTB |= 0b00001000 ;
  PORTB &= ~0b00001000 ;
  }

  for (int i=0; i<8; i++) 
  {
  if (segbuf[segcnt] & (0x80 >> i))
  PORTB |= 0b00000100 ;
  else
  PORTB &= ~0b00000100 ;
  PORTB |= 0b00001000 ;
  PORTB &= ~0b00001000 ;
  }
    
  PORTB |= 0b00010000 ;
  segcnt ++ ;
  segcnt &= NDIGITS_MASK ;
}
#endif

void setup()
{
    pinMode(latchpin, OUTPUT) ;
    pinMode(clockpin, OUTPUT) ;
    pinMode(datapin, OUTPUT) ;

    Serial.begin(9600) ;
    Timer1.initialize(2000);      // 4 ms
    Timer1.attachInterrupt(LED_irq) ;
    Timer1.start() ;
}

void loop()
{
  for (;;) 
  {
       if (millis() >= (previousTime))
       {
         previousTime = previousTime + 1000;  
         seconds = seconds +1;
         if (seconds == 60)
         {
            seconds = 0;
            minutes = minutes +1;
         }
         if (minutes == 60)
         {
            minutes = 0;
            hours = hours +1;
         }
        Serial.print (hours, DEC);
        Serial.print (":");
        Serial.print (minutes,DEC);
        Serial.print (":");
        Serial.println(seconds,DEC);
        } 
    
       segbuf[0] = seg[hours / 10] ;
       segbuf[1] = seg[hours % 10] ;
      
       segbuf[3] = seg[minutes / 10] ;
       segbuf[4] = seg[minutes % 10] ;
      
       segbuf[6] = seg[seconds / 10] ;
       segbuf[7] = seg[seconds % 10] ;
       delay(1000) ;
       }
}
