/**
 * @file RelojManager.cpp
 * @brief Implementación de la gestión del tiempo y sincronización de red.
 * @details Desarrolla la lógica para arrancar el RTC físico, conectarse a redes Wi-Fi,
 * consultar servidores horarios de internet (NTP) y dar un formato limpio de dos dígitos
 * a las variables de tiempo para su despliegue visual.
 * @date Junio 2026
 */

#include "RelojManager.h"
#include <WiFi.h>
#include "time.h"

RelojManager::RelojManager() {
    // Constructor vacío (Las configuraciones inician formalmente en iniciar())
}

bool RelojManager::iniciar() {
    // Intentamos establecer comunicación con el integrado DS1307 en su dirección I2C fija
    if (!rtc.begin()) {
        Serial.println("[ERROR] No se detecta el hardware del DS1307.");
        return false;
    }
    return true;
}

void RelojManager::sincronizarHoraPorWiFi(const char* ssid, const char* password) {
    Serial.println("[NTP] Conectando a Wi-Fi para actualizar hora...");
    WiFi.begin(ssid, password);

    // Bucle de espera: Máximo 15 segundos (30 intentos x 500ms) a que se asocie a la red física
    int intentosWifi = 0;
    while (WiFi.status() != WL_CONNECTED && intentosWifi < 30) {
        delay(500);
        Serial.print(".");
        intentosWifi++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\n[NTP] ¡Conectado al Wi-Fi con éxito!");
        
        // TIEMPO DE ESPERA CRÍTICO: 
        // Dejamos pasar 3 segundos para que el router estabilice la IP del ESP32
        Serial.println("[NTP] Esperando estabilidad de red (3s)...");
        delay(3000); 
        
        // Configurar la zona horaria 
        configTime(-18000, 0, "pool.ntp.org", "time.nist.gov");
        
        struct tm timeinfo;
        bool horaObtenida = false;
        int intentosNTP = 0;
        
        // Bucle de reintentos para el servidor de internet
        while (!horaObtenida && intentosNTP < 5) {
            intentosNTP++;
            Serial.printf("[NTP] Intentando obtener hora (Intento %d de 5)...\n", intentosNTP);
            
            // Si el servidor NTP responde, pasamos los datos del sistema directamente al integrado RTC
            if (getLocalTime(&timeinfo)) {
                horaObtenida = true;

                // Inyectamos la hora de internet directo al chip físico DS1307
                rtc.adjust(DateTime(
                    timeinfo.tm_year + 1900, 
                    timeinfo.tm_mon + 1, 
                    timeinfo.tm_mday, 
                    timeinfo.tm_hour, 
                    timeinfo.tm_min, 
                    timeinfo.tm_sec
                ));
                Serial.println("[NTP] ¡Módulo DS1307 sincronizado con éxito!");
            } else {
                Serial.println("[WARNING] Servidor ocupado. Esperando 2 segundos para reintentar...");
                delay(2000); 
            }
        }
        
        if (!horaObtenida) {
            Serial.println("[ERROR FINAL] No se pudo obtener la hora tras 5 intentos.");
        }
        
    } else {
        Serial.println("\n[ERROR Wi-Fi] No se pudo conectar a la red.");
    }

    // Mantener el wifi un instante antes de desconectar por seguridad
    delay(2000);

    // Apagamos completamente el Wi-Fi para evitar ruidos electromagnéticos 
    // en las líneas de los mánagers analógicos/I2C y optimizar el consumo eléctrico.
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    Serial.println("[NTP] Wi-Fi apagado correctamente. Bucle local iniciado.");
}

String RelojManager::formatearDosDigitos(int numero) {
    // Si el valor numérico es de un solo dígito, le concatenamos un "0" a la izquierda
    if (numero < 10) {
        return "0" + String(numero);
    }
    return String(numero);
}

String RelojManager::obtenerHora() {
    // Captura los registros actuales del chip de tiempo
    DateTime ahora = rtc.now(); 
    
    int hora24 = ahora.hour();
    int minuto = ahora.minute();
    int segundo = ahora.second();
    
    // 1. Corrección del reloj para Tener AM y PM evitar error de 00.
    // (Ej: Las 12:00. es PM, las 00:00 es 12:00 AM)
    String periodo = (hora24 >= 12) ? " PM" : " AM";
    
    // 2. Convertir el formato de 24 horas a un rango de 0 a 11
    int hora12 = hora24 % 12;
     
    // lo obligamos a transformarse en 12 para evitar el "00".
    if (hora12 == 0) {
        hora12 = 12;
    }
    
    // 4. Retornamos la cadena final armada con tu método de formato de ceros
    return formatearDosDigitos(hora12) + ":" +
           formatearDosDigitos(minuto) + ":" +
           formatearDosDigitos(segundo) +
           periodo;
}

String RelojManager::obtenerFecha() {
    // Captura los registros actuales del chip de tiempo
    DateTime ahora = rtc.now();
    return formatearDosDigitos(ahora.day()) + "/" +
           formatearDosDigitos(ahora.month()) + "/" +
           String(ahora.year());
}