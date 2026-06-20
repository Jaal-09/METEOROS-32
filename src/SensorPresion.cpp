/**
 * @file SensorPresion.cpp
 * @brief Implementación del sensor de presión atmosférica y umbrales climáticos.
 * @date Junio 2026
 */

#include "SensorPresion.h"

/**
 * @brief Constructor. Acopla el nombre, unidad y el puntero al hardware BME280.
 * @param instance Puntero a la instancia compartida del BME280.
 */
SensorPresion::SensorPresion(Adafruit_BME280* instance) 
    : Sensor("Presion", "hPa"), bme(instance) {}

/**
 * @brief Confirma la conexión con la capa de abstracción.
 * @return true de forma inmediata.
 */
bool SensorPresion::iniciar() {
    return true;
}

/**
 * @brief Obtiene la lectura física de presión y la convierte de Pascales a Hectopascales.
 * @return float Presión atmosférica en hPa.
 */
float SensorPresion::leerValor() {
    return bme->readPressure() / 100.0F; 
}

/**
 * @brief Evalúa la presión actual para determinar el pronóstico del clima.
 * @details Clasifica el estado según los umbrales locales: Lluvioso (<775 hPa), 
 * Nublado (775-784 hPa) o Despejado (>784 hPa).
 * @return String Cadena de texto con el diagnóstico ("Lluvioso", "Nublado", "Despejado").
 */
String SensorPresion::obtenerEstadoTexto() {
    float presion = leerValor();
    if (presion < 775.0)  return "Lluvioso";
    if (presion <= 784.0) return "Nublado";
    return "Despejado";
}