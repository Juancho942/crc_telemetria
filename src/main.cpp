#include <Arduino.h>
#include <sensor.h>
#include <Adafruit_LiquidCrystal.h>
#include "Wire.h"
#include <crc.h>

byte vector[20];
int direccionDestino = 2000;
sensor Sensor0(A0, 2000, " °C");
sensor Sensor1(A1, 2000, " °C");
sensor sensor2(A2, 2000, " cm");
crc sensor3(0b1001101);

// initialize the library with the numbers of the interface pins
Adafruit_LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{   Serial.begin(9600);
    // set up the LCD's number of rows and columns:
    lcd.begin(16, 2);

}
void acomodar(byte lecturaSensor1[20], byte rangoMinimo , byte rangoMaximo, float valor){
  char lecturaSensor[7];
  byte cerosIncrementar = 0;
  String cadenaDatos;
  byte b = 0;
  cadenaDatos = String(valor);
  cadenaDatos.toCharArray(lecturaSensor,7);
  for (int i = 0; i <=5; i++){
    if( lecturaSensor[i] != '.'){
      cerosIncrementar += 1;
    }
    else{
      break;
    }
  }
  cerosIncrementar = 3 - cerosIncrementar;
  if (cerosIncrementar > 0){
    for (int i = 5; i >=0; i--){
        if( i < cerosIncrementar){
          lecturaSensor[i] = 48;
        }
        else{
          lecturaSensor[i] = lecturaSensor[i-cerosIncrementar];
      }
    }
  }
  for (int i = rangoMinimo; i <= rangoMaximo; i++){
    lecturaSensor1[i] = lecturaSensor[b];
    b += 1;
  }
}
void adecuar_sondeo_individual(byte datoRepuestaIndividual[20]){
    byte direccionDestinoL = direccionDestino & 0x00ff;
    byte direccionDestinoH = (direccionDestino >> 8) & 0x00ff;
    datoRepuestaIndividual[0] = 1;//SOH
    datoRepuestaIndividual[1] = Sensor0.origen_H();
    datoRepuestaIndividual[2] = Sensor0.origen_L();
    datoRepuestaIndividual[3] = direccionDestinoH;
    datoRepuestaIndividual[4] = direccionDestinoL;
    datoRepuestaIndividual[5] = 63;//?
    datoRepuestaIndividual[6] = 2;//STX
    datoRepuestaIndividual[10] = Sensor0.lecturaSensor();
    acomodar(datoRepuestaIndividual,7,12,Sensor0.lecturaSensor());
    datoRepuestaIndividual[13] = 32;
    datoRepuestaIndividual[14] = 32;
    datoRepuestaIndividual[15] = 167;
    datoRepuestaIndividual[16] = 67;
    datoRepuestaIndividual[17] = 3;//ETX
    datoRepuestaIndividual[18] = 0; // CRC
    datoRepuestaIndividual[19] = 4;//EOT

}

void loop()
{ 
    lcd.clear();
    adecuar_sondeo_individual(vector);
    lcd.setCursor(0, 0);
    lcd.print("calculo CRC");
    lcd.setCursor(1,1);
    int lectura1 = sensor3.calculoCrc(vector);
    lcd.print(lectura1);
    //Serial.print(sensor3.calculoCrc(vector));
    lcd.setCursor(10,1);
    lcd.print(Sensor0.lecturaSensor());
    delay(500);
}
