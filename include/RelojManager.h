#ifndef RELOJ_MANAGER_H
#define RELOJ_MANAGER_H

#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>

class RelojManager {
private:
    RTC_DS1307 rtc;
    String formatearDosDigitos(int numero);

public:
    RelojManager();
    bool iniciar();
    void sincronizarHoraPorWiFi(const char* ssid, const char* password);
    String obtenerHora();
    String obtenerFecha();
};

#endif