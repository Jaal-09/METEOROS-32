#include "SensorTemperatura.h"

SensorTemperatura::SensorTemperatura(Adafruit_BME280* instance) 
    : Sensor("Temperatura", "C"), bme(instance) {}

bool SensorTemperatura::iniciar() {
    return true; 
}

float SensorTemperatura::leerValor() {
    float tempRaw = bme->readTemperature();
    return tempRaw - 3; // Calibración por calor residual de la TFT
}

String SensorTemperatura::obtenerEstadoTexto() {
    return ""; // No aplica diagnóstico textual para temperatura
}