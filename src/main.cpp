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
void adecuar_sondeo_individual(byte datoRepuestaIndividual[20]){
    byte direccionDestinoH = direccionDestino & 0x00ff;
    byte direccionDestinoL = (direccionDestino >> 8) & 0x00ff;
    datoRepuestaIndividual[0] = 1;//SOH
    datoRepuestaIndividual[1] = Sensor0.origen_H();
    datoRepuestaIndividual[2] = Sensor0.origen_L();
    datoRepuestaIndividual[3] = direccionDestinoH;
    datoRepuestaIndividual[4] = direccionDestinoL;
    datoRepuestaIndividual[5] = 63;//?
    datoRepuestaIndividual[6] = 2;//STX
    datoRepuestaIndividual[7] = '*';
    datoRepuestaIndividual[8] = '*';
    datoRepuestaIndividual[9] = '*';
    datoRepuestaIndividual[10] = Sensor0.lecturaSensor();
    datoRepuestaIndividual[11] = '*';
    datoRepuestaIndividual[11] = '*';
    datoRepuestaIndividual[12] = '*';
    datoRepuestaIndividual[12] = '*';
    datoRepuestaIndividual[13] = '*';
    datoRepuestaIndividual[14] = '*';
    datoRepuestaIndividual[15] = '*';
    datoRepuestaIndividual[16] = '*';
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
    lcd.print(sensor3.calculoCrc(vector));
    Serial.print(sensor3.calculoCrc(vector));
    lcd.setCursor(10,1);
    lcd.print(Sensor0.lecturaSensor());
    delay(3000);
}
