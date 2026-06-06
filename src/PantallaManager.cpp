#include "PantallaManager.h"

//Los pines se cargan directamente desde el platformio.ini
PantallaManager::PantallaManager() {
    
}

void PantallaManager::iniciar() {
    tft.init();
    tft.setRotation(1); 
}