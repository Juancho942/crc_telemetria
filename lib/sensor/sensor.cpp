#include <Arduino.h>
#include <sensor.h>

sensor::sensor(uint8_t pinLectura, int direccionSensor,  String unidaSensor)
{
    _pinLectura = pinLectura;
    _direccionSensor = direccionSensor;
    _unidaSensor = unidaSensor;

    pinMode(_pinLectura, OUTPUT);
}

void sensor::adecuacion()
{
}
float sensor::lecturaSensor()
{
    int lectura = analogRead(_pinLectura);
    float lectura1 = map(lectura,0.00,1023.00,0.00,200.00);
    return lectura1;
}
byte sensor::origen_H()
{
    byte direccionOrigenH = (_direccionSensor >> 8) & 0x00ff;
    return direccionOrigenH;
}
byte sensor::origen_L()
{
    byte direccionOrigenL = _direccionSensor & 0x00ff;
    return direccionOrigenL;
}
String sensor::unidad()
{
    return _unidaSensor;
}