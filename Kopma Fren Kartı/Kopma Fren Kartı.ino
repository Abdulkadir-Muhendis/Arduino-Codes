//Abdulkadir MÜHENDİS, M.Sc.
//Filkar Otomotiv A.Ş.
//Kopma code 2020

int I1 = A1;
int I2 = A2;
int O1 = 10;
int I1_val = 0;
int I2_val = 0;
float I1_voltage = 0.0;
float I2_voltage = 0.0;
float I1_pressure = 0.0;
float I2_pressure = 0.0;
float Fark_degeri = 0.0;

void setup() {
  Serial.begin(9600);
  pinMode(I1, INPUT);
  pinMode(I2, INPUT);
  pinMode(O1, OUTPUT);
}

void loop() {
  I1_val = analogRead(A1);  
  delay(10);
  I2_val = analogRead(A2);  
  delay(10);
  
  I1_voltage = ((I1_val/255.75)+1); // To be between 1-5 V!
  I2_voltage = ((I2_val/255.75)+1); // To be between 1-5 V!

  I1_pressure = (I1_val-1)*4;
  I2_pressure = (I2_val-1)*4;

  Fark_degeri = I1_voltage - I2_voltage;

  if(I1_val - I2_val >= 31) // bit
    digitalWrite(O1, HIGH); 
  else
    digitalWrite(O1, LOW); 
//
//    Serial.print("\n I1 gerilimi: ");
//    Serial.print(I1_voltage);
//
//    Serial.print("\n I2 gerilimi: ");
//    Serial.print(I2_voltage);
    
    Serial.print("\n I1 Değeri: ");
    Serial.print(I1_val);
    Serial.print(" Bit");
    Serial.print("\t I2 Değeri: ");
    Serial.print(I2_val);
    Serial.print(" Bit");
    Serial.print("\t Fark Değeri: ");
    Serial.print(Fark_degeri);
    Serial.print(" V");

}
