#ifndef sensor_h
#define sensor_h

#include <Arduino.h>

class sensor
{
private:
    uint8_t _pinLectura;
    int _direccionSensor;
    String _unidaSensor;
    float _lecturaSensor;
    float _lecturaTiempoPasado;
    float _rangoMinimo;
    float _rangoMaximo;
    

public:
    sensor(uint8_t pinLectura, int direccionSensor, String unidaSensor, float rangoMinimo, float rangoMaximo);
    void adecuacion();
    byte origen_H();
    byte origen_L();
    String unidad();
    float lecturaSensor();
    float porcentajeLectura(float porcentaje);
};

#endif
