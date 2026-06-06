#include <Arduino.h>
#include "PantallaManager.h"

PantallaManager miPantalla;

unsigned long tiempoUltimaActualizacion = 0;
const unsigned long INTERVALO_TFT = 2500; 
bool primeraActualizacion = true;