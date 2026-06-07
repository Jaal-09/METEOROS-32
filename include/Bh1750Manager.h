#ifndef BH1750_MANAGER_H
#define BH1750_MANAGER_H

#include <Arduino.h>
#include <Wire.h>
#include <BH1750.h>

class Bh1750Manager {
private:
    BH1750 lightSensor;
    bool sensorOperativo;

public:
    Bh1750Manager();
    bool iniciar();
    float obtenerLuz();
};

#endif