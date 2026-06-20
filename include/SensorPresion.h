/**
 * @file SensorPresion.h
 * @brief Clase derivada para el control y lectura de la presión atmosférica.
 * @date Junio 2026
 */

#ifndef SENSOR_PRESION_H
#define SENSOR_PRESION_H

#include "Sensor.h"
#include <Adafruit_BME280.h>

/**
 * @class SensorPresion
 * @brief Especialización de la clase Sensor para gestionar el barómetro del BME280.
 */
class SensorPresion : public Sensor {
private:
    Adafruit_BME280* bme; /**< Puntero a la instancia física compartida del BME280. */

public:
    /**
     * @brief Constructor. Configura el nombre "Presión", la unidad "hPa" y enlaza el hardware.
     * @param instance Puntero al objeto Adafruit_BME280 activo.
     */
    SensorPresion(Adafruit_BME280* instance);

    /**
     * @brief Valida la disponibilidad del sensor barométrico.
     * @return true si el sensor está listo.
     */
    bool iniciar() override;

    /**
     * @brief Captura la presión atmosférica actual corregida a hectopascales.
     * @return float Presión en hPa.
     */
    float leerValor() override;

    /**
     * @brief Entrega el pronóstico del clima ("Despejado", "Nublado", "Lluvioso") según la presión.
     * @return String Cadena con el diagnóstico meteorológico textual.
     */
    String obtenerEstadoTexto() override;
};

#endif