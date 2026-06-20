/**
 * @file SensorHumedad.h
 * @brief Clase derivada encargada del control y lectura de la humedad relativa.
 * @details Implementa los métodos de la clase abstracta base 'Sensor' para adaptarlos
 * al comportamiento del sensor BME280.
 * @date Junio 2026
 */

#ifndef SENSOR_HUMEDAD_H
#define SENSOR_HUMEDAD_H

#include "Sensor.h"
#include <Adafruit_BME280.h>

/**
 * @class SensorHumedad
 * @brief Especialización de la clase Sensor para gestionar las lecturas de humedad ambiental.
 */
class SensorHumedad : public Sensor {
private:
    /**
     * @brief Puntero al dispositivo físico BME280.
     * @details Apunta a la instancia central del BME280 que reside en el orquestador principal. 
     * Esto permite compartir el mismo chip físico en el bus I2C con los managers de 
     * temperatura y presión, optimizando el uso de la memoria RAM del ESP32.
     */
    Adafruit_BME280* bme;

public:
    /**
     * @brief Constructor de la clase SensorHumedad.
     * @details Invoca internamente al constructor de la clase base `Sensor`, asignándole 
     * el nombre fijo "Humedad" y la unidad "%". Además, enlaza el puntero local con el 
     * sensor físico compartido.
     * @param instance Puntero a la instancia del objeto Adafruit_BME280 que ya fue creado e inicializado.
     */
    SensorHumedad(Adafruit_BME280* instance);

    /**
     * @brief Valida la disponibilidad del sensor de humedad.
     * @note Sobrescribe (`override`) el método virtual puro de la clase base.
     * @return true si el puntero al hardware es válido y está listo para operar, false en caso contrario.
     */
    bool iniciar() override;

    /**
     * @brief Captura y retorna el valor actual de la humedad relativa del aire.
     * @details Ejecuta las rutinas internas de la librería de Adafruit para extraer la 
     * lectura directa procesada en porcentaje.
     * @return float Porcentaje de humedad relativa actual en el entorno (0.0% a 100.0%).
     */
    float leerValor() override;

    /**
     * @brief Analiza el porcentaje de humedad para ofrecer un diagnóstico textual del clima.
     * @details Evalúa si el ambiente se encuentra en rangos secos, óptimos o excesivamente 
     * húmedos.
     * @return String Cadena de texto descriptiva.
     */
    String obtenerEstadoTexto() override;
};

#endif