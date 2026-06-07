#include <Arduino.h>
#include "PantallaManager.h"
#include "RelojManager.h"
#include "Bme280Manager.h"

PantallaManager miPantalla;
RelojManager miReloj;
Bme280Manager miBme;

unsigned long tiempoUltimaActualizacion = 0;
unsigned long tiempoUltimoCambioVista = 0;

const unsigned long INTERVALO_TFT = 1000;       
const unsigned long INTERVALO_VISTA = 7000;     
bool primeraActualizacion = true;               

// Configuracion WIFI
const char* WIFI_SSID = "mg52"; 
const char* WIFI_PASS = "wifi1234"; 

void setup() {
    Serial.begin(115200);
    delay(500);
    
    Serial.println("[SISTEMA] Iniciando TFT y Reloj...");
    miPantalla.iniciar();
    miReloj.iniciar();
    miBme.iniciar();
    
    miPantalla.mostrarTexto("Sincronizando hora ...", 10, 100, 2, TFT_WHITE, TFT_NAVY);
    
    // Llamamos a la sincronización automática por Wi-Fi
    miReloj.sincronizarHoraPorWiFi(WIFI_SSID, WIFI_PASS);
    
    delay(1000);
}

void loop() {
    if (millis() - tiempoUltimaActualizacion >= INTERVALO_TFT) {
        tiempoUltimaActualizacion = millis();
        
        if (primeraActualizacion) {
            miPantalla.limpiarPantalla(TFT_NAVY);
            miPantalla.iniciar(); 
            primeraActualizacion = false; 
        }
        
        String horaActual  = miReloj.obtenerHora();
        String fechaActual = miReloj.obtenerFecha();
        
        // Lecturas reales del sensor BME280
        float t_real = miBme.obtenerTemperatura();
        float h_real = miBme.obtenerHumedad();

        //Agregado leer presion real
        float p_real = miBme.obtenerPresion();     
        
        float l_simulada = 420.0; // Se mantiene fija hasta conectar el BH1750

        // Imprimimos también la presión en el Monitor Serie para verificar
        Serial.printf("[SISTEMA] Temp: %.1f C | Hum: %.1f %% | Pres: %.1f hPa\n", t_real, h_real, p_real);
        
        // le pasamos los 6 parámetros requeridos (incluye p_real al final)
        miPantalla.actualizarInterfaz(horaActual, fechaActual, t_real, h_real, l_simulada, p_real);
    }

    if (millis() - tiempoUltimoCambioVista >= INTERVALO_VISTA) {
        tiempoUltimoCambioVista = millis();
        miPantalla.cambiarVista();
    }
}
