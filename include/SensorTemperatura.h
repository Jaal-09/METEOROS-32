#ifndef SENSOR_TEMPERATURA_H
#define SENSOR_TEMPERATURA_H

#include "Sensor.h"
#include <Adafruit_BME280.h>

class SensorTemperatura : public Sensor {
private:
    Adafruit_BME280* bme;
public:
    SensorTemperatura(Adafruit_BME280* instance);
    bool iniciar() override;
    float leerValor() override;
    String obtenerEstadoTexto() override;
};

#endif