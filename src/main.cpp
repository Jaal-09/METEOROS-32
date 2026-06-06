#include <Arduino.h>
#include "PantallaManager.h"

PantallaManager miPantalla;

unsigned long tiempoUltimaActualizacion = 0;
const unsigned long INTERVALO_TFT = 2500; 
bool primeraActualizacion = true;

//Se inicia la pantalla tft
void setup() {
    Serial.begin(115200);
    delay(500);
    
    Serial.println("[SISTEMA] Iniciando TFT ...");
    miPantalla.iniciar();
    
    // Mostramos el texto de carga de forma temporal
    miPantalla.mostrarTexto("Iniciando Panel TFT ...", 60, 100, 2, TFT_WHITE);
    delay(1500);
}

void loop() {
    if (millis() - tiempoUltimaActualizacion >= INTERVALO_TFT) {
        tiempoUltimaActualizacion = millis();
        
        //Se borra el texto de iniciando pantalla
        if (primeraActualizacion) {
            // Se usa la función limpiarPantalla
            miPantalla.limpiarPantalla(TFT_NAVY);
            
            // Volvemos a llamar a iniciar para que redibuje los marcos fijos y el título
            miPantalla.iniciar(); 
            
            // Apagamos la bandera para que no lo vuelva a hacer
            primeraActualizacion = false; 
        }
        
        float t_simulada = 26.7;
        float h_simulada = 55.2;
        float l_simulada = 385.0;
        
        Serial.println("[SISTEMA] Refrescando interfaz grafica.");
        miPantalla.actualizarInterfaz(t_simulada, h_simulada, l_simulada);
    }
}