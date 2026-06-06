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