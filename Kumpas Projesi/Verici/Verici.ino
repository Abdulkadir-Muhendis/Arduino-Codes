#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
RF24 verici(9, 10);    //kütüphane tarafından kullanılacak pinleri tanımlıyoruz
float musa = 0.0;
const uint64_t kanal = 0xE8E8F0F0E1LL ; //kanalı tanımlıyoruz
int bit_array[25]; // For storing the data bit. bit_array[0] = data bit 1 (LSB), bit_array[23] = data bit 24 (MSB).
int bit_arrayy[25];
unsigned long time_now;   // For storing the time when the clock signal is changed from HIGH to LOW (falling edge trigger of data output).

int CLOCK_PIN = 4;
int DATA_PIN = 3;

void setup(void) {
  verici.begin();       //nrf yi başlatıyoruz
  verici.openWritingPipe(kanal);  //kanal id sı tanımlanıyor
  Serial.begin(115200);
  pinMode(CLOCK_PIN, INPUT);
  pinMode(DATA_PIN, INPUT);
}


void decode() {
  int sign = 1;
  int i = 0;
  float value = 0.0;
  float result = 0.0;




  bit_array[i] = digitalRead(DATA_PIN);       // Store the 1st bit (start bit) which is always 1.
  while (digitalRead(CLOCK_PIN) == HIGH) {};

  for (i = 1; i <= 24; i++) {
    while (digitalRead(CLOCK_PIN) == LOW) { } // Wait until clock returns to HIGH
    bit_array[i] = digitalRead(DATA_PIN);
    while (digitalRead(CLOCK_PIN) == HIGH) {} // Wait until clock returns to LOW
  }

  for (i = 0; i <= 24; i++) {                 // Show the content of the bit array. This is for verification only.
  }

  for (i = 1; i <= 20; i++) {                 // Turning the value in the bit array from binary to decimal.
    value = value + (pow(2, i - 1) * bit_array[i]);
  }

  if (bit_array[21] == 1) sign = -1;          // Bit 21 is the sign bit. 0 -> +, 1 => -

  if (bit_array[24] == 1) {                   // Bit 24 tells the measureing unit (1 -> in, 0 -> mm)


    result = (value * sign) / 2000.00;
    Serial.print(result, 3);                  // Print result with 3 decimals
    Serial.println(" in");
  } else {
    result = (value * sign) / 100.00;
    musa = result;
    Serial.print(result, 2);                  // Print result with 2 decimals
    Serial.println(" mm");
  }
  delay(1);


/*
  if (verici.available())
  {
    verici.write(bit_array, 25);
    Serial.println("verici hazır");
  }*/
  
}


void loop() {

  while (digitalRead(CLOCK_PIN) == LOW) {}  // If clock is LOW wait until it turns to HIGH
  time_now = micros();
  while (digitalRead(CLOCK_PIN) == HIGH) {} // Wait for the end of the HIGH pulse
  if ((micros() - time_now) > 500) {        // If the HIGH pulse was longer than 500 micros we are at the start of a new bit sequence
    decode(); //decode the bit sequence
  }


    //char bit_arrayy[25] = "Hello AbdurKadir!!!";
        verici.write (&musa, (25.0) );

        
       //verici.write(sizeof(musa), sizeof(25));

  //   verici.write(bit_array, 25);  //mesaj değişkeni yollanıyor
  // Serial.print("verici hazır1");


}
