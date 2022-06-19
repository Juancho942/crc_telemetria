#ifndef sensor_h
#define sensor_h

#include <Arduino.h>

class sensor
{
private:
    uint8_t _pinLectura;
    int _direccionSensor;
    String _unidaSensor;

public:
    sensor(uint8_t pinLectura, int direccionSensor, String unidaSensor);
    void adecuacion();
    byte origen_H();
    byte origen_L();
    String unidad();
    float lecturaSensor();
};

#endif
