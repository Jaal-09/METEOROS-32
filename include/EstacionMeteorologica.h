/**
 * @file EstacionMeteorologica.h
 * @brief Orquestador central de la estación meteorológica METEOROS-32.
 * @details Esta clase actúa como el "cerebro" del sistema. Se encarga de integrar
 * y coordinar el hardware de los sensores, el reloj de tiempo real (RTC), la pantalla TFT
 * y la interacción con el usuario mediante un botón físico, usando programación no bloqueante.
 * @date Junio 2026
 */

#ifndef ESTACION_METEOROLOGICA_H
#define ESTACION_METEOROLOGICA_H

#include <Arduino.h>
#include <Adafruit_BME280.h>
#include "PantallaManager.h"
#include "RelojManager.h"
#include "Sensor.h"

/**
 * @class EstacionMeteorologica
 * @brief Gestiona el ciclo de vida, la lectura de sensores y el flujo principal de la estación.
 */
class EstacionMeteorologica {
private:
    // ---- Control de Periféricos e Interacción ----
    int pinBoton;                   /**< Pin GPIO del ESP32 donde se conecta el botón físico para cambiar de menú. */
    bool estadoBotonAnterior;       /**< Almacena el último estado leído del botón para detectar pulsaciones exactas y evitar rebotes. */

    // ---- Control de Tiempo No Bloqueante (Concurrencia) ----
    unsigned long tiempoUltimaActualizacion; /**< Guarda el rastro en milisegundos (millis) del último refresco de la pantalla. */
    const unsigned long INTERVALO_TFT;       /**< Tiempo de espera fijo entre actualizaciones de la interfaz para evitar parpadeos (Ghosting). */
    bool primeraActualizacion;               /**< Bandera de control para forzar el dibujado de la estructura gráfica completa en el primer arranque. */

    // ---- Credenciales de Red ----
    const char* ssid;               /**< Nombre (SSID) de la red Wi-Fi local para la sincronización horaria por internet. */
    const char* password;           /**< Contraseña de la red Wi-Fi. */

    // ---- Componentes y Mánagers del Sistema ----
    PantallaManager pantalla;       /**< Instancia encargada de renderizar los recuadros, textos e iconos en la pantalla TFT. */
    RelojManager reloj;             /**< Instancia encargada de administrar la hora local y la sincronización NTP. */
    
    // ---- Capa de Sensores y Arquitectura POO ----
    Adafruit_BME280 bmeFisico;      /**< Objeto físico compartido del sensor BME280 conectado al bus I2C. */

    /**
     * @brief Arreglo polimórfico de sensores heredados.
     * @details Contiene punteros hacia las instancias de los diferentes sensores de la estación
     * (Temperatura, Humedad, Presión, Luz). Permite recorrerlos dinámicamente mediante un bucle genérico.
     */
    Sensor* misSensores[4];

public:
    /**
     * @brief Constructor de la estación meteorológica.
     * @details Recibe la configuración inicial del hardware (pin del botón) y las credenciales de red,
     * configurando internamente los intervalos de tiempo por defecto para la pantalla.
     * @param pinBoton Número de pin del botón físico de navegación.
     * @param wifiSSID Nombre de la red Wi-Fi.
     * @param wifiPASS Contraseña de la red Wi-Fi.
     */
    EstacionMeteorologica(int pinBoton, const char* wifiSSID, const char* wifiPASS);
    
    /**
     * @brief Destructor de la clase.
     * @details Se encarga de liberar de manera segura la memoria dinámica que se reservó 
     * en el Heap para el arreglo de sensores polimórficos, evitando fugas de memoria.
     */
    ~EstacionMeteorologica();
    
    /**
     * @brief Inicializa todo el ecosistema de la estación.
     * @details Configura el pin del botón, arranca el bus I2C, inicializa la pantalla TFT, 
     * activa el reloj RTC conectándose a Wi-Fi para calibrarlo y prepara el arreglo de sensores.
     * @return void
     */
    void iniciar();
    
    /**
     * @brief Hilo de ejecución principal de la estación (Debe llamarse en el loop).
     * @details Monitorea de forma continua si el botón fue pulsado para cambiar de vista de inmediato.
     * Al mismo tiempo, y sin detener el programa, evalúa si ya pasó el tiempo necesario para leer 
     * los sensores y refrescar los datos en la pantalla TFT.
     * @return void
     */
    void procesar();
};

#endif