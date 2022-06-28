#include <Arduino.h>
#include <crc.h>

crc::crc(byte numeroCrc)
{
    for (int i = 0; i < 7; i++)
    {
        _comparacionXor[i] = bitRead(numeroCrc, i);
    }
}
byte crc::calculoCrc(byte vector[20])
{
    for (int i = 0; i < 20; i++)
    {
        _vector[i] = vector[i];
    }

    byte calculo_crc[136];
    byte G[7] = {1, 0, 0, 1, 1, 0, 1};
    byte vectorTemporal[7];
    int a = 0;
    int caso = 0;
    int cerosIncrementar = 7;
    boolean cicloGeneral;
    memset(calculo_crc, 3, 136);
    for (int i = 1; i < 18; i++)
    { // empiezo a recorrer byte por byte de la cadena de datos
        int b = 0;
        for (int j = 0; j < 136; j++)
        {
            // Serial.println("calculando posicion vector");
            if (calculo_crc[j] != 3)
            {
                b += 1;
            }
            else
                break;
        }
        a = 7;
        for (int j = b; j < (b + 8); j++)
        {
            calculo_crc[j] = bitRead(_vector[i], a);
            a -= 1;
        }
    }
    int posiciones;
    for (int i = 0; i < 136; i++)
    {
        vectorTemporal[7 - cerosIncrementar] = calculo_crc[i];
        cerosIncrementar -= 1;
        cicloGeneral = true;
        if (cerosIncrementar == 0)
        {
            Serial.println();
            while (cicloGeneral)
            {
                if (caso == 0)
                {
                    int j = 0;
                    while (vectorTemporal[j] == 0)
                    {
                        cerosIncrementar += 1;
                        j += 1;
                    }
                    if (cerosIncrementar > 0)
                    {
                        posiciones = 0;
                        for (int b = 0; b < 7 - cerosIncrementar; b++)
                        {
                            vectorTemporal[b] = vectorTemporal[b + cerosIncrementar];
                            posiciones += 1;
                        }
                        cicloGeneral = false;
                    }
                    caso = 1;
                }

                else if (caso == 1)
                {
                    for (int c = 0; c < 7; c++)
                    { // realiza la xor
                        vectorTemporal[c] = G[c] ^ vectorTemporal[c];
                    }
                    caso = 0;
                }
            }
        }
    }
    byte retorno = 0;
    posiciones -= 1;
    for (int i = 0; i < 7; i++)
    {
        bitWrite(retorno, posiciones, vectorTemporal[i]);
        posiciones -= 1;
        if (posiciones == 0) break;
    }
    return (retorno);
}
