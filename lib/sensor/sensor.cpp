#include <Arduino.h>
#include <sensor.h>

sensor::sensor(uint8_t pinLectura, int direccionSensor, String unidaSensor,
               float rangoMinimo, float rangoMaximo)
{
    _pinLectura = pinLectura;
    _direccionSensor = direccionSensor;
    _unidaSensor = unidaSensor;
    _rangoMinimo = rangoMinimo;
    _rangoMaximo = rangoMaximo;
    pinMode(_pinLectura, OUTPUT);
    _lecturaTiempoPasado = 0;
}

void sensor::adecuacion()
{
}
float sensor::lecturaSensor()
{   
    int lectura = analogRead(_pinLectura);
    _lecturaSensor = lectura;
    return _lecturaSensor;
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
float sensor::porcentajeLectura(float porcentaje)
{   float lectura = lecturaSensor();
    _lecturaSensor = map(lectura, 0.00, 1023.00, _rangoMinimo, _rangoMaximo);
    float porcentajeLecturaActual = map(_lecturaSensor, _rangoMinimo, _rangoMaximo, 0.00, 100.00);
    float porcentajeLecturaPasada = map(_lecturaTiempoPasado, _rangoMinimo, _rangoMaximo, 0.00, 100.00);
    if ((porcentajeLecturaActual - porcentajeLecturaPasada) > 10)
    {
        _lecturaTiempoPasado = _lecturaSensor;
        return (porcentajeLecturaActual); 
    }
    else if ((porcentajeLecturaPasada - porcentajeLecturaActual) > 10)
    { 
        _lecturaTiempoPasado = _lecturaSensor; 
        return (porcentajeLecturaActual);
    }
    else
        return (0);
    
}
