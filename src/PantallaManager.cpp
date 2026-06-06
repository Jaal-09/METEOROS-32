#include "PantallaManager.h"

//Los pines se cargan directamente desde el platformio.ini
PantallaManager::PantallaManager() {
    
}

void PantallaManager::iniciar() {

    tft.init();
    tft.setRotation(1); 

    tft.fillRect(0, 0, 320, 240, TFT_NAVY); 
    delay(50);

    //Banner
    tft.fillRect(0, 0, 320, 38, TFT_BLUE);

    // Configuración del título
    tft.setTextColor(TFT_WHITE, TFT_BLUE);
    tft.setTextSize(2);
    tft.drawString("ESTACION METEOROLOGICA", 30, 10);

    //Contenedores para la información de ejemplo a mostrar
    tft.drawRect(10, 50, 300, 45, TFT_RED);
    tft.drawRect(10, 105, 300, 45, TFT_CYAN);
    tft.drawRect(10, 160, 300, 45, TFT_YELLOW);

    // Pie de página fijo
    tft.drawLine(0, 218, 320, 218, TFT_SILVER);
    tft.setTextColor(TFT_SILVER, TFT_NAVY);
    tft.setTextSize(1);
    tft.drawString("U. DE PAMPLONA - MECATRÓNICA", 45, 224);
}

void PantallaManager::limpiarPantalla(uint16_t color) {
    tft.fillScreen(color);
}


void PantallaManager::mostrarTexto(String texto, int x, int y, int tamano, uint16_t color) {
    //Color para el texto
    tft.setTextColor(color, TFT_NAVY);

    //tamaño del texto
    tft.setTextSize(tamano);

    //dibujamos
    tft.drawString(texto, x, y); 
}

void PantallaManager::actualizarInterfaz(float temp, float hum, float lux) {
    // Mandamos los datos con coordenadas ajustadas para que queden centrados en los rectángulos
    String strTemp = "TEMP: " + String(temp, 1) + " C ";
    mostrarTexto(strTemp, 25, 62, 3, TFT_RED);
    
    String strHum = "HUM:  " + String(hum, 1) + " % ";
    mostrarTexto(strHum, 25, 117, 3, TFT_CYAN);
    
    String strLux = "LUX:  " + String(lux, 0) + " lx ";
    mostrarTexto(strLux, 25, 172, 3, TFT_YELLOW);
}
