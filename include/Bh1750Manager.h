#ifndef BH1750_MANAGER_H
#define BH1750_MANAGER_H

#include <Arduino.h>
#include <Wire.h>
#include <BH1750FVI.h>

class Bh1750Manager {
private:
    BH1750FVI lightSensor;
    bool sensorOperativo;

public:
    Bh1750Manager();
    bool iniciar();
    float obtenerLuz();
};

#endif