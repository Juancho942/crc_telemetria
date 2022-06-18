#ifndef crc_h
#define crc_h

#include <Arduino.h>

class crc
{
private:
    byte _vector[136];
    byte _comparacionXor[7];
public:
    crc(byte numeroCrc);
    byte calculoCrc(byte vector[20]);
};

#endif
