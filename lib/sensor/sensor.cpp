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
    _valorSensor = 0;
    _booleangSensor = true;
}

void sensor::adecuacion()
{
}
float sensor::lecturaSensor()
{   
     if (_booleangSensor)
    {   
        int lectura = analogRead(_pinLectura);
        _lecturaSensor = map(lectura, 0.00, 1023.00, _rangoMinimo, _rangoMaximo);
        _valorSensor = _lecturaSensor;
    }
    _booleangSensor = false;
    return _valorSensor;
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
    float porcentajeLecturaActual = map(lectura, _rangoMinimo, _rangoMaximo, 0.00, 100.00);
    float porcentajeLecturaPasada = map(_lecturaTiempoPasado, _rangoMinimo, _rangoMaximo, 0.00, 100.00);
    if (abs(porcentajeLecturaActual - porcentajeLecturaPasada) > porcentaje)
    {
        _lecturaTiempoPasado = _valorSensor;
        return (porcentajeLecturaActual); 
    }
    else
        return (0);
    
}
float sensor::ValorSensor()
{
  return _valorSensor;

}

void sensor::booleanLectura()
{
    _booleangSensor = true;
    _lecturaTiempoPasado = _valorSensor;
}
