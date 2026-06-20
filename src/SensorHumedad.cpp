/**
 * @file SensorHumedad.cpp
 * @brief Implementación del sensor de humedad relativa.
 * @date Junio 2026
 */

#include "SensorHumedad.h"

/**
 * @brief Constructor. Acopla el nombre, unidad y el puntero al hardware BME280.
 * @param instance Puntero a la instancia compartida del BME280.
 */
SensorHumedad::SensorHumedad(Adafruit_BME280* instance) 
    : Sensor("Humedad", "% RH"), bme(instance) {}

/**
 * @brief Confirma la conexión con la capa de abstracción.
 * @return true de forma inmediata.
 */
bool SensorHumedad::iniciar() {
    return true;
}

/**
 * @brief Obtiene la lectura física de humedad desde el BME280.
 * @return float Porcentaje de humedad relativa (%).
 */
float SensorHumedad::leerValor() {
    return bme->readHumidity();
}

/**
 * @brief Retorna el diagnóstico textual del estado de la humedad.
 * @return String Cadena de texto (por ahora vacía).
 */
String SensorHumedad::obtenerEstadoTexto() {
    return "";
}