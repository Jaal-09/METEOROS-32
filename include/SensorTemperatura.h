/**
 * @file SensorTemperatura.h
 * @brief Clase derivada para el control y lectura de la temperatura ambiental.
 * @date Junio 2026
 */

#ifndef SENSOR_TEMPERATURA_H
#define SENSOR_TEMPERATURA_H

#include "Sensor.h"
#include <Adafruit_BME280.h>

/**
 * @class SensorTemperatura
 * @brief Especialización de la clase Sensor para gestionar el termómetro del BME280.
 */
class SensorTemperatura : public Sensor {
private:
    Adafruit_BME280* bme; /**< Puntero a la instancia física compartida del BME280. */

public:
    /**
     * @brief Constructor. Configura el nombre "Temperatura", la unidad "C" y enlaza el hardware.
     * @param instance Puntero al objeto Adafruit_BME280 activo.
     */
    SensorTemperatura(Adafruit_BME280* instance);

    /**
     * @brief Valida la disponibilidad del sensor térmico.
     * @return true si el sensor está listo.
     */
    bool iniciar() override;

    /**
     * @brief Captura la temperatura ambiental actual en grados Celsius.
     * @return float Temperatura en grados centígrados (°C).
     */
    float leerValor() override;

    /**
     * @brief Retorna el diagnóstico textual del estado de la temperatura.
     * @return String Cadena de texto (por ahora vacía).
     */
    String obtenerEstadoTexto() override;
};

#endif