#ifndef PANTALLA_MANAGER_H
#define PANTALLA_MANAGER_H

#include <Arduino.h>
#include <TFT_eSPI.h> 

class PantallaManager {
private:
    TFT_eSPI tft;
    // 1 = Principal (Hora/Fecha/Temp), 2 = Secundaria (Hum/Lux)
    int vistaActual; 

public:
    PantallaManager();
    void iniciar();
    void limpiarPantalla(uint16_t color);
    void mostrarTexto(String texto, int x, int y, int tamano, uint16_t color, uint16_t fondo);
    // Al tocar la pantalla cambiará de estado
    void cambiarVista(); 
    void actualizarInterfaz(String hora, String fecha, float temp, float hum, float lux);
};

#endif