# SENSOR-VL53L0X---CODE
ARDUINO CODE VL53L0X TIME OF FLYGHT
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Adafruit_VL53L0X.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Pinout para la OLED
#define OLED_MOSI   9
#define OLED_CLK    10
#define OLED_DC     11
#define OLED_CS     12
#define OLED_RESET  13

// Inicializar la pantalla OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  Serial.begin(9600);

  // Esperar hasta que el puerto serial se abra para dispositivos USB nativos
  while (!Serial) {
    delay(1);
  }

  Serial.println("Prueba de Sensor de Distancia VL53L0X");

  // Inicializar el sensor de distancia
  if (!lox.begin()) {
    Serial.println(F("Error al inicializar VL53L0X"));
    while (1);
  }

  // Inicializar la pantalla OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("Fallo en la asignación de la Pantalla OLED"));
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1.5);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Inicializando...");
  display.display();
