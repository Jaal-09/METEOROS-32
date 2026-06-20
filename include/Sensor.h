/**
 * @file Sensor.h
 * @brief Clase base abstracta (interfaz) para la gestión unificada de sensores.
 * @details Define el "contrato de programación" obligatorio que todos los sensores
 * de la estación METEOROS-32 deben cumplir. Al ser una clase abstracta pura, no permite
 * la creación de objetos directos; en su lugar, sirve de plantilla para que las clases hijas
 * (Temperatura, Humedad, Presión, Luz) hereden sus propiedades e implementen su propia lógica.
 * @date Junio 2026
 */

#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

/**
 * @class Sensor
 * @brief Plantilla y modelo base para la abstracción y polimorfismo de los sensores del sistema.
 */
class Sensor {
protected:
    // Atributos protegidos: Accesibles por las clases hijas, pero ocultos para el mundo exterior.
    String nombre; /**< Nombre identificador del sensor  */
    String unidad; /**< Unidad de medida física del sensor en formato de texto (Ej: "C", "hPa", "lx"). */

public:
    /**
     * @brief Constructor de la clase base Sensor.
     * @details Inicializa los atributos básicos de identidad que todo sensor del sistema comparte.
     * @param nom Cadena de texto con el nombre del sensor.
     * @param uni Cadena de texto con la unidad de medida correspondiente.
     */
    Sensor(String nom, String uni) : nombre(nom), unidad(uni) {}

    /**
     * @brief Destructor virtual de la clase Sensor.
     * @details  Al trabajar con polimorfismo, el destructor de la clase 
     * base DEBE ser virtual. Esto asegura que al destruir un puntero de tipo `Sensor*`, se invoque 
     * primero el destructor de la clase hija específica, liberando correctamente la memoria de cada hardware.
     */
    virtual ~Sensor() {}

    /**
     * @brief Inicializa el hardware o protocolo específico del sensor.
     * @note Obliga a cada clase hija a implementar su propia rutina de arranque.
     * @return true si el sensor se inicializó y respondió correctamente, false en caso de falla.
     */
    virtual bool iniciar() = 0;

    /**
     * @brief Realiza la lectura física del sensor y procesa el valor numérico.
     * @note  Cada sensor hija ejecutará sus propias librerías de conversión.
     * @return float El valor de la variable física medido en tiempo real.
     */
    virtual float leerValor() = 0;

    /**
     * @brief Evalúa el valor actual del sensor y devuelve un diagnóstico en texto amigable.
     * @note Permite obtener estados como "Despejado", "Lluvioso" o "Soleado".
     * @return String Cadena de texto con la interpretación del estado actual del entorno.
     */
    virtual String obtenerEstadoTexto() = 0;

    /**
     * @brief Método Getter para recuperar el nombre del sensor.
     * @return String Nombre del sensor.
     */
    String getNombre() const { return nombre; }

    /**
     * @brief Método Getter para recuperar la unidad de medida del sensor.
     * @return String Unidad de medida.
     */
    String getUnidad() const { return unidad; }
};

#endif