#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"           //Modül ile ilgili kütüphaneleri ekliyoruz
char bit_array[25];
float musa_1;
RF24 alici (9, 10);
const uint64_t kanal = 0xE8E8F0F0E1LL; //kanalı tanımlıyoruz
void setup() {
  Serial.begin(115200);             //Seri iletişimi başlatıyoruz.
  alici.begin();                  //nRF24 iletişimini başlatıyoruz.
  alici.openReadingPipe(1, kanal); //Programın data göndereceği alıcının adresini ayarlıyoruz.
  alici.startListening();

}

void loop() {

  //Eğer iletişim uygunsa
  if (alici.available())
  {
    alici.read(&musa_1, sizeof (musa_1));  //Gelen datayı oku
    Serial.print (musa_1);
        Serial.println ("  mm");
        
    delay(10);
  }
}
