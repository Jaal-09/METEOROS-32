/**
 * @file Sensor.h
 * @brief Interfaz base abstracta para los sensores.
 * @date Junio 2026
 */

#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

class Sensor {
protected:
    String nombre;
    String unidad;

public:
    Sensor(String nom, String uni) : nombre(nom), unidad(uni) {}
    virtual ~Sensor() {}

    virtual bool iniciar() = 0;
    virtual float leerValor() = 0;
    virtual String obtenerEstadoTexto() = 0;

    String getNombre() const { return nombre; }
    String getUnidad() const { return unidad; }
};

#endif