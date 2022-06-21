#include <Arduino.h>
#include <crc.h>

crc::crc(byte numeroCrc)
{
    Serial.println(int(numeroCrc));
    Serial.println('\n');
    for (int i = 0; i < 7; i++)
    {
        _comparacionXor[i] = bitRead(numeroCrc, i);
        // Serial.print(int(_comparacionXor[i]));
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
    int z, c, a = 0;
    memset(calculo_crc, 3, 136);
    for (int i = 1; i < 18; i++)
    { // empiezo a recorrer byte por byte de la cadena de datos
        Serial.print(i);
        Serial.println(" for para convertir los binarios de vector con i : ");
        int b = 0;
        for (int j = 0; j < 136; j++)
        {
            Serial.println("calculando posicion vector");
            if (calculo_crc[j] != 3)
            {
                b += 1;
            }
            else
                break;
        }
        Serial.print("b: ");
        Serial.println(b);
        a = 7;
        for (int j = b; j < (b + 8); j++)
        {
            Serial.print("for que saca los binarios de cada byte con j : ");
            Serial.println(j);
            calculo_crc[j] = bitRead(_vector[i], a);
            a -= 1;
        }
        for (int i = 0; i < 136; i++)
        {
            Serial.print(calculo_crc[i]);
        }
        Serial.println();
    }
    boolean variable = true;
    while (variable)
    {

        for (int z = 0; z < 7; z++)
        { // copio los binarliios que se bajan del vector principal
            Serial.println("copio los binarios ");
            vectorTemporal[z] = calculo_crc[c];
            c += 1;
        }
        for (int i = 0; i < 7; i++)
        { // realiza la xor
            temp[i] = G[i] ^ vectorTemporal[i];
            //Serial.println("realiza la operacion xor");
            Serial.print(temp[i]);
        }
        z = 0;
        while (temp[z] == 0)
        { // cuento de ceros
            Serial.println("ingreso while que me cuenta los ceros a mover");
            bandera += 1; // incremento la variable el numero de ceros q se va contanto
            z += 1;
        }
        if (bandera != 0)
        { // verifico si hubo conteo de ceros y realizo los respectivos cambios
            Serial.println("ingreso if verificar cuantos ceros a mover");
            for (int i = 0; i < (7 - bandera); i++)
            {
                Serial.println("ingreso for");
                vectorTemporal[i] = temp[z]; // elimino de la variable los ceros empezando a copiarla de a donde se encontro el primer uno
                z += 1;
                variable = false;
            }
            bandera = 0;
        }
    }

    byte retorno;
    for (int i = 0; i < 7; i++)
    {
        bitWrite(retorno, temp[i], (6 - i));
    }
    return (retorno);
}
