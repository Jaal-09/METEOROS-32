# 🌦️ Estación Meteorológica IoT — ESP32

## 📝 Descripción del Proyecto
Este proyecto consiste en el desarrollo y programación de una **Estación Meteorológica Automatizada de Alta Precisión** basada en el microcontrolador **ESP32**. El sistema unifica la captura de múltiples variables ambientales de interés meteorológico, la administración del tiempo local mediante sincronización en la nube y una interfaz gráfica dinámica operada mediante hardware externo.

Desarrollado como un sistema de firmware robusto en **PlatformIO** bajo el framework de **Arduino**, el código implementa principios avanzados de separación de hardware mediante programación orientada a objetos (Managers de Control) y aislamiento físico de periféricos usando múltiples buses I2C para optimizar la estabilidad de las lecturas.

---

## 🏛️ Institución y Autoría
* **Institución:** Universidad de Pamplona
* **Programa:** Ingeniería Mecatrónica  
* **Autores:**

- Jesus Alberto Arias Lizcano
- Andrés Stivent Cortés Gomez 
- Darwin David Naranjo Calderón
- Karen Daniela Suárez Rico

* **Fecha:** Junio 2026    

---

## 🏗️ Arquitectura del Sistema (Mánagers de Control)
El firmware del proyecto está estructurado bajo un modelo modular, donde cada periférico físico posee su propia abstracción lógica (archivos `.h` y `.cpp` dedicados dentro de `include/` y `src/`):

1. **`Bme280Manager` (Ambiente):** Controla el sensor integrado Adafruit BME280 para extraer lecturas calibradas de temperatura (°C), humedad relativa (% RH) y presión atmosférica (hPa).
2. **`Bh1750Manager` (Luminosidad):** Gestiona el luxómetro digital BH1750 para medir la iluminancia en Lux (lx) y procesar un diagnóstico natural del entorno en texto (Oscuridad, Interior, Sol Directo).
3. **`RelojManager` (Tiempo):** Administra el chip de tiempo real (RTC) DS1307. Cuenta con lógica de conexión Wi-Fi temporizada para interrogar servidores horarios **NTP** (`pool.ntp.org`), ajustar la zona horaria fija (**UTC-5** para Colombia) y apagar el módulo de radiofrecuencia (`WIFI_OFF`) para eliminar interferencias electromagnéticas.
4. **`PantallaManager` (Interfaz Gráfica):** Controla la renderización en el panel TFT ILI9341 a través de la librería `TFT_eSPI`. Implementa un menú cíclico de dos vistas:
   * **Vista 1:** Fecha, hora digital en tiempo real y temperatura ambiente.
   * **Vista 2:** Detalles avanzados de humedad, presión atmosférica y estado natural de luz.

---

## Conexiones Físicas (Mapeo de Pines)

### 📊 Configuración de Buses I2C (Aislamiento de Periféricos)
Para evitar colisiones de direcciones en el bus y disminuir la capacitancia parásita en las líneas de datos, se han levantado dos buses I2C independientes dentro del ESP32.

### 📌 Tabla Completa de Asignación de Pines

| Periférico / Componente | Pin Físico Pantalla/Sensor | Pin GPIO ESP32 | Tipo de Bus / Función |
| :--- | :--- | :--- | :--- |
| **Pulsador Externo** | Pin NO / Signal | **GPIO 5** | Entrada Digital con Pull-Up Interno |
| **Sensor Luxómetro BH1750** | SDA | **GPIO 21** | Bus I2C Nativo (`Wire`) |
| **Sensor Luxómetro BH1750** | SCL | **GPIO 22** | Bus I2C Nativo (`Wire`) |
| **Reloj Físico RTC DS1307** | SDA | **GPIO 21** | Bus I2C Nativo (`Wire`) |
| **Reloj Físico RTC DS1307** | SCL | **GPIO 22** | Bus I2C Nativo (`Wire`) |
| **Sensor Ambiental BME280** | SDA | **GPIO 18** | Bus I2C Secundario (`Wire1`) |
| **Sensor Ambiental BME280** | SCL | **GPIO 19** | Bus I2C Secundario (`Wire1`) |
| **Pantalla TFT ILI9341** | TFT_RD (Read) | **GPIO 4** | Control Bus Paralelo 8-bits |
| **Pantalla TFT ILI9341** | TFT_WR (Write) | **GPIO 33** | Control Bus Paralelo 8-bits |
| **Pantalla TFT ILI9341** | TFT_DC (Data/Cmd) | **GPIO 32** | Control Bus Paralelo 8-bits |
| **Pantalla TFT ILI9341** | TFT_CS (Chip Sel) | **GPIO 2** | Control Bus Paralelo 8-bits |
| **Pantalla TFT ILI9341** | TFT_RST (Reset) | **GPIO 15** | Control Bus Paralelo 8-bits |
| **Pantalla TFT ILI9341** | TFT_D0 | **GPIO 12** | Bus de Datos Paralelo (Bit 0) |
| **Pantalla TFT ILI9341** | TFT_D1 | **GPIO 13** | Bus de Datos Paralelo (Bit 1) |
| **Pantalla TFT ILI9341** | TFT_D2 | **GPIO 26** | Bus de Datos Paralelo (Bit 2) |
| **Pantalla TFT ILI9341** | TFT_D3 | **GPIO 25** | Bus de Datos Paralelo (Bit 3) |
| **Pantalla TFT ILI9341** | TFT_D4 | **GPIO 17** | Bus de Datos Paralelo (Bit 4) |
| **Pantalla TFT ILI9341** | TFT_D5 | **GPIO 16** | Bus de Datos Paralelo (Bit 5) |
| **Pantalla TFT ILI9341** | TFT_D6 | **GPIO 27** | Bus de Datos Paralelo (Bit 6) |
| **Pantalla TFT ILI9341** | TFT_D7 | **GPIO 14** | Bus de Datos Paralelo (Bit 7) |

---

## 💻 Características del Firmware e Inmunidad a Fallos
* **Algoritmo de Debounce Mecánico:** La conmutación de pantallas mediante el botón del GPIO 5 se gestiona mediante control por flanco de bajada combinada con un retardo controlado de 250ms para absorber rebotes eléctricos espurios.
* **Aislamiento en Arranque:** Si un sensor se desconecta físicamente o falla en el arranque, la bandera `sensorOperativo` conmuta a `false`. El firmware evita bloqueos en el bucle principal (`loop`), devolviendo valores seguros `0.0` y notificando el estado en pantalla.
* **Formateo Estricto de Datos:** Se implementa un método privado de conversión de cadenas (`formatearDosDigitos`) para garantizar la simetría visual en el reloj digital, anteponiendo ceros cuando los valores son menores a 10.

---

## 🛠️ Tecnologías y Librerías Utilizadas
El entorno de compilación está gestionado por las siguientes dependencias oficiales especificadas en el archivo `platformio.ini`:

* **`bodmer/TFT_eSPI` (v2.5.43):** Driver de renderizado de alta velocidad modificado para operar bajo bus paralelo de 8 bits (`ESP32_PARALLEL=1`).
* **`adafruit/RTClib` (v2.1.4):** Interfaz para la lectura y ajuste del integrado DS1307.
* **`adafruit/Adafruit BME280 Library` (v2.2.4):** API para la captura y compensación matemática de datos termo-higro-barométricos.
* **`claws/BH1750` (v1.3.0):** Driver del luxómetro configurado en Modo Continuo de Alta Resolución (Mide constantemente cada 120ms).

---

## 🚀 Estructura de Archivos

   ```text
   ├── include/
   │   ├── Bh1750Manager.h
   │   ├── Bme280Manager.h
   │   ├── PantallaManager.h
   │   └── RelojManager.h
   ├── src/
   │   ├── Bh1750Manager.cpp
   │   ├── Bme280Manager.cpp
   │   ├── PantallaManager.cpp
   │   ├── RelojManager.cpp
   │   └── main.cpp
   └── platformio.ini