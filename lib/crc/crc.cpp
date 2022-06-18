#include <Arduino.h>
#include <crc.h>


crc::crc(byte numeroCrc)
{
    for (int i = 0; i < 7; i++)
    {
        _comparacionXor[0] = numeroCrc & 0b01000000;
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
    byte temp[7];
    byte vectorTemporal[7];
    int bandera = 0;
    int b, z, c, a = 0;
    for (int i = 1; i < 18; i++)
    { // empiezo a recorrer byte por byte de la cadena de datos
        a = 7;
        for (b; b < (b += 8); b++)
        {
            calculo_crc[b] = bitRead(_vector[i], a);
            a -= 1;
        }
        while (b == 137)
        { // verifico que ya se haya pasado todos los binarios al vector

            for (z; z < 7; z++)
            { // copio los binarliios que se bajan del vector principal
                vectorTemporal[z] = calculo_crc[c];
                c += 1;
            }
            z = 0;
            for (int i = 0; i < 7; i++)
            { // realiza la xor
                temp[i] = G[i] ^ vectorTemporal[i];
            }
            while (temp[z] == 0)
            {                 // cuento de ceros
                bandera += 1; // incremento la variable el numero de ceros q se va contanto
                z += 1;
            }
            if (bandera != 0)
            { // verifico si hubo conteo de ceros y realizo los respectivos cambios
                for (int i = 0; i < (7 - bandera); i++)
                {
                    vectorTemporal[i] = temp[z]; // elimino de la variable los ceros empezando a copiarla de a donde se encontro el primer uno
                    z += 1;
                    bandera = 0;
                }
            }
            if (c >= 136)
            { // verifico si ya se llego al final del vector general y salgo del while
                b = 0;
                break;
            }
        }
    }
    byte retorno;
    for (int i = 0; i < 7; i++)
    {
        bitWrite(retorno, temp[i], (6 - i));
    }
    return (retorno);
}
