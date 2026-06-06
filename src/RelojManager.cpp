#include "RelojManager.h"

RelojManager::RelojManager() {
    // Constructor vacío, el bus I2C se inicia en el método iniciar
}

bool RelojManager::iniciar() {

    // Intentar enlazar con el chip físico por la dirección I2C nativa
    if (!rtc.begin()) {
        Serial.println("[ERROR] No se detecta el hardware del DS1307.");
        return false;
    }

    // Si es la primera vez que se monta
    if (!rtc.isrunning()) {
        Serial.println("[RTC] El reloj no estaba corriendo. Sincronizando con la hora de compilacion...");

        // Ajusta el reloj con la fecha y hora exacta en la que se le dio "Upload" 
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
    
    Serial.println("[RTC] Inicializado correctamente.");
    return true;
}

String RelojManager::formatearDosDigitos(int numero) {

    // Agrega un cero a la izquierda si el número es menor a 10 
    if (numero < 10) {
        return "0" + String(numero);
    }
    return String(numero);
}

String RelojManager::obtenerHora() {
    DateTime ahora = rtc.now();
    return formatearDosDigitos(ahora.hour()) + ":" +
           formatearDosDigitos(ahora.minute()) + ":" +
           formatearDosDigitos(ahora.second());
}

String RelojManager::obtenerFecha() {
    DateTime ahora = rtc.now();
    return formatearDosDigitos(ahora.day()) + "/" +
           formatearDosDigitos(ahora.month()) + "/" +
           String(ahora.year());
}