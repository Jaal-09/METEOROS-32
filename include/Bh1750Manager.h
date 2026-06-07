#ifndef BH1750_MANAGER_H
#define BH1750_MANAGER_H

#include <Arduino.h>
#include <Wire.h>
#include <BH1750.h>

class Bh1750Manager {
private:
    BH1750 luxometro;
    uint8_t direccionI2C;
    int pinSDA;
    int pinSCL;
    bool sensorOperativo;

public:
    // Constructor con el nuevo nombre de la clase (Pines 21 y 22 por defecto)
    Bh1750Manager(uint8_t direccion = 0x23, int sda = 21, int scl = 22);
    
    bool iniciar();
    float obtenerLux();
    void mostrarLecturaSerial();
};

#endif