/**
 * @file EstacionMeteorologica.cpp
 * @brief Implementación de la lógica central y orquestación de la estación meteorológica.
 * @details Desarrolla el ciclo de vida principal del sistema, encargándose de la gestión
 * de memoria dinámica en el Heap para los sensores, el control de los dos buses físicos I2C,
 * la captura polimórfica de telemetría y la máquina de estados del botón de navegación.
 * @date Junio 2026
 */

#include "EstacionMeteorologica.h"
#include "SensorTemperatura.h"
#include "SensorHumedad.h"
#include "SensorPresion.h"
#include "SensorLuz.h"

/**
 * @brief Constructor de la clase EstacionMeteorologica.
 * @details Inicializa las variables de control de tiempo en cero, define el refresco de pantalla 


 * @param pinBoton Puerto GPIO asignado para el botón del menú.
 * @param wifiSSID Nombre de la red inalámbrica para el acceso a internet.
 * @param wifiPASS Clave de seguridad de la red Wi-Fi.
 */
EstacionMeteorologica::EstacionMeteorologica(int pinBoton, const char* wifiSSID, const char* wifiPASS)
    : pinBoton(pinBoton), INTERVALO_TFT(1000), ssid(wifiSSID), password(wifiPASS) {
    
    tiempoUltimaActualizacion = 0;
    primeraActualizacion = true;
    estadoBotonAnterior = HIGH; // Se inicializa en ALTO asumiendo configuración Pull-Up

    // Creación dinámica de objetos. Los sensores BME280 comparten la misma instancia de hardware físico.
    misSensores[0] = new SensorTemperatura(&bmeFisico);
    misSensores[1] = new SensorHumedad(&bmeFisico);
    misSensores[2] = new SensorPresion(&bmeFisico);
    misSensores[3] = new SensorLuz(); // El sensor de luz BH1750 opera de forma independiente
}

/**
 * @brief Destructor de la clase EstacionMeteorologica.
 * @details Operación crítica para el ESP32. Libera de forma ordenada los bloques de memoria 
 * del Heap que fueron reservados en el constructor mediante 'delete'.

 */
EstacionMeteorologica::~EstacionMeteorologica() {
    for (int i = 0; i < 4; i++) {
        delete misSensores[i];
    }
}

/**
 * @brief Inicializa los periféricos de hardware, protocolos de comunicación y servicios de internet.
 * @details Configura la velocidad del puerto serial a 115200 baudios, establece el pin del botón como 
 * entrada con resistencia Pull-Up interna y realiza una de las tareas más importantes del proyecto:
 * **Separar los buses I2C**. Levanta Wire1 en los pines 18 y 19 exclusivamente para el chip BME280, 
 * y Wire nativo en los pines 21 y 22 para el BH1750, evitando colisiones en las líneas físicas. 
 * Finalmente, conecta a la red para obtener la hora por NTP.
 * @return void
 */
void EstacionMeteorologica::iniciar() {
    Serial.begin(115200);
    delay(500);
    
    pinMode(pinBoton, INPUT_PULLUP);
    pantalla.iniciar();
    reloj.iniciar();
    
    // 1. Levantar Bus Secundario Wire1 (Pines 18 y 19) para el integrado físico BME280
    Wire1.begin(18, 19);
    if (!bmeFisico.begin(0x76, &Wire1)) {
        Serial.println("[ERROR] ¡No se encontró el chip físico BME280!");
    }

    // 2. Levantar Bus Primario Wire nativo (Pines 21 y 22) e inicializar el sensor de luz heredado
    Wire.begin(21, 22);
    misSensores[3]->iniciar(); 
    
    pantalla.mostrarTexto("Iniciando Sistema NTP...", 15, 100, 2, TFT_WHITE, TFT_NAVY);
    reloj.sincronizarHoraPorWiFi(ssid, password);
    delay(1000);
}

/**
 * @brief Hilo de control y ejecución en tiempo real de la estación meteorológica.
 * @details Gestiona dos subprocesos fundamentales de manera concurrente (no bloqueante):
 * * 1. **Muestreo y Telemetría:** Cada vez que transcurre el intervalo de un segundo (evaluado con millis), 
 * invoca de forma **polimórfica pura** el método `leerValor()` de cada sensor en el arreglo. No importa qué
 * sensor sea, la clase sabe cómo extraer el número real. Luego, adquiere los diagnósticos de texto 
 * calculados internamente por los sensores, lanza la telemetría por consola serial y refresca la TFT.
 * * 2. **Lectura Asíncrona del Botón:** Monitorea al instante los flancos de bajada en el pin digital (cuando 
 * pasa de HIGH a LOW), cambiando la pantalla de menú inmediatamente y reajustando los temporizadores locales 
 * con un retraso controlado de 250ms para absorber rebotes eléctricos (Debounce por software).
 * @return void
 */
void EstacionMeteorologica::procesar() {
    // ---- Bloque Tarea 1: Muestreo de datos cada segundo ----
    if (millis() - tiempoUltimaActualizacion >= INTERVALO_TFT) {
        tiempoUltimaActualizacion = millis();
        
        if (primeraActualizacion) {
            pantalla.limpiarPantalla(TFT_NAVY);
            pantalla.iniciar(); 
            primeraActualizacion = false; 
        }
        
        // Recuperación de la hora civil procesada AM/PM
        String horaActual  = reloj.obtenerHora();
        String fechaActual = reloj.obtenerFecha();
        
        // Ejecución de llamadas polimórficas puras por su función heredada
        float t_real = misSensores[0]->leerValor();
        float h_real = misSensores[1]->leerValor();
        float p_real = misSensores[2]->leerValor();
        float l_real = misSensores[3]->leerValor();
        
        // Adquisición de estados textuales (Ej: "Despejado", "Poca Luz")
        String estadoPresion = misSensores[2]->obtenerEstadoTexto();
        String estadoLuz     = misSensores[3]->obtenerEstadoTexto();

        // Salida formateada de telemetría por consola Orientada a Objetos [TELEMETRIA OO]
        Serial.printf("[TELEMETRIA OO] Temp: %.1f C | Hum: %.1f %% | Pres: %.1f hPa (%s) | Luz: %.1f lx | %s\n", 
                      t_real, h_real, p_real, estadoPresion.c_str(), l_real, estadoLuz.c_str());
        
        // Envío de datos puros a la capa gráfica para su renderizado
        pantalla.actualizarInterfaz(horaActual, fechaActual, t_real, h_real, l_real, p_real, estadoLuz, estadoPresion);
    }

    // ---- Bloque Tarea 2: Monitoreo instantáneo del botón físico ----
    bool estadoBotonActual = digitalRead(pinBoton);
    if (estadoBotonAnterior == HIGH && estadoBotonActual == LOW) { // Detección de flanco de bajada
        pantalla.cambiarVista();
        tiempoUltimaActualizacion = 0; // Fuerza un refresco gráfico inmediato con los datos en la nueva vista
        delay(250); // Retraso de estabilización mecánica (anti-rebote)
    }
    estadoBotonAnterior = estadoBotonActual;
}