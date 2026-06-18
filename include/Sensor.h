/**
 * @file Sensor.h
 * @brief Interfaz abstracta para la gestión de sensores.
 * @date Junio 2026
 */

#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

class Sensor {
protected:
    String nombre;  /**< Identificador del sensor. */
    String unidad;  /**< Unidad de medida (ej: °C, %, lx, hPa). */

public:
    Sensor(String nom, String uni) : nombre(nom), unidad(uni) {}
    virtual ~Sensor() {}

    /** @brief Inicialización obligatoria del hardware. */
    virtual bool iniciar() = 0;
    
    /** @brief Captura y retorna el valor numérico procesado. */
    virtual float leerValor() = 0;
    
    /** @brief Retorna el diagnóstico textual si aplica (Lluvioso, Oscuro, etc). */
    virtual String obtenerEstadoTexto() = 0;

    String getNombre() const { return nombre; }
    String getUnidad() const { return unidad; }
};

#endif