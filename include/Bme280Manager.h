#ifndef BME280_MANAGER_H
#define BME280_MANAGER_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BME280.h>

class Bme280Manager {
private:
    Adafruit_BME280 bme;
    bool sensorOperativo;

public:
    Bme280Manager();
    bool iniciar();
    
    float obtenerTemperatura();
    float obtenerHumedad();
    float obtenerPresion();
};

#endif