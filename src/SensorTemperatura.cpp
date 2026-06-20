/**
 * @file SensorTemperatura.cpp
 * @brief Implementación del sensor de temperatura y su calibración.
 * @date Junio 2026
 */

#include "SensorTemperatura.h"

/**
 * @brief Constructor. Acopla el nombre, unidad y el puntero al hardware BME280.
 * @param instance Puntero a la instancia compartida del BME280.
 */
SensorTemperatura::SensorTemperatura(Adafruit_BME280* instance) 
    : Sensor("Temperatura", "C"), bme(instance) {}

/**
 * @brief Confirma la conexión con la capa de abstracción.
 * @return true de forma inmediata.
 */
bool SensorTemperatura::iniciar() {
    return true; 
}

/**
 * @brief Obtiene la lectura térmica del BME280 aplicando un offset de calibración.
 * @details Resta 3°C al valor para compensar el calor residual disipado por la pantalla TFT.
 * @return float Temperatura corregida en grados Celsius (°C).
 */
float SensorTemperatura::leerValor() {
    float tempRaw = bme->readTemperature();
    return tempRaw - 3; 
}

/**
 * @brief Retorna el diagnóstico textual del estado de la temperatura.
 * @return String Cadena de texto.
 */
String SensorTemperatura::obtenerEstadoTexto() {
    return ""; 
}