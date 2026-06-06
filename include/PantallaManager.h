#ifndef PANTALLA_MANAGER_H
#define PANTALLA_MANAGER_H

#include <Arduino.h>
#include <TFT_eSPI.h> 

class PantallaManager {
private:
    TFT_eSPI tft;

public:
    PantallaManager();
    void iniciar();
    void limpiarPantalla(uint16_t color);
    void mostrarTexto(String texto, int x, int y, int tamano, uint16_t color);
    void actualizarInterfaz(float temp, float hum, float lux);
};

#endif