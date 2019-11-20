// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include "RTClib.h"
//#include "LiquidCrystal.h"
RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Pazar", "Pazartesi", "Sali", "Carsamba", "Persembe", "Cuma", "Cumartesi"};
//LiquidCrystal lcd(8,9,4,5,6,7);
void setup () {
  //lcd.begin(16,2);
  while (!Serial);

  Serial.begin(9600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
     rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));// Soooooooooooooooooo important for reset 
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}
void loop () {
    DateTime now = rtc.now();
    
    //lcd.setCursor(0,0);
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    //Serial.setCursor(0,1);
    Serial.print(now.day(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.year(), DEC); 
    delay(100);
}
