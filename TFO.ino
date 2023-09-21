#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Adafruit_VL53L0X.h"

// Definiciones de la pantalla OLED y sensor VL53L0X
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_MOSI   9
#define OLED_CLK    10
#define OLED_DC     11
#define OLED_CS     12
#define OLED_RESET  13

// Inicializar la pantalla OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
Adafruit_VL53L0X lox = Adafruit_VL53L0X(); // Crear una instancia del sensor VL53L0X

void setup() {
  Serial.begin(9600);

  // Esperar hasta que el puerto serial se abra para dispositivos USB nativos
  while (!Serial) {
    delay(1);
  }

  Serial.println("Prueba de Sensor de Distancia VL53L0X");

  // Inicializar el sensor de distancia VL53L0X
  if (!lox.begin()) {
    Serial.println(F("Error al inicializar VL53L0X"));
    while (1);
  }

  // Inicializar la pantalla OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("Fallo en la asignación de la Pantalla OLED"));
    while (1);
  }

  // Limpieza inicial de la pantalla y mensaje de inicialización
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Inicializando...");
  display.display();
  delay(2000);
  display.clearDisplay();
  display.display();
}

void displayTimeOfFlight(double duration) {
  // Limpiar la pantalla y establecer un fondo negro
  display.clearDisplay();
  display.fillScreen(SSD1306_BLACK);
  
  // Configurar el tamaño del texto y el color en blanco
  display.setTextSize(1.2);
  display.setTextColor(SSD1306_WHITE);
  
  // Mostrar el título "Tiempo de Vuelo:"
  display.setCursor(0, 10);
  display.println("Tiempo de Vuelo:");
  
  // Mostrar el valor de tiempo de vuelo
  display.setTextSize(2.5);
  display.setCursor(10, 35);
  display.print(duration, 1);
  display.setTextSize(1);
  display.print(" ps");
  
  // Actualizar la pantalla con el contenido
  display.display();
}

void displayOutOfRange() {
  // Limpiar la pantalla y establecer un fondo negro
  display.clearDisplay();
  display.fillScreen(SSD1306_BLACK);
  
  // Configurar el tamaño del texto y el color en blanco
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  // Mostrar el mensaje "Fuera de Rango"
  display.setCursor(15, 15);
  display.println("Fuera de Rango");
  
  // Actualizar la pantalla con el contenido
  display.display();
}

void loop() {
  VL53L0X_RangingMeasurementData_t medida;

  // Realizar una prueba de rango con el sensor VL53L0X
  lox.rangingTest(&medida, false);

  // Calcular el tiempo de vuelo en picosegundos
  double duration = medida.RangeMilliMeter * 2.0 * 3.335640952;

  // Mostrar resultado del tiempo de vuelo si no está fuera de rango
  if (medida.RangeStatus != 4) {
    static double prevDuration = -1.0; // Valor anterior de duración
    if (prevDuration != duration) {
      displayTimeOfFlight(duration);
      Serial.print("Tiempo de Vuelo: "); Serial.print(duration, 1); Serial.println(" ps");
      prevDuration = duration; // Actualizar el valor anterior
    }
  } else {
    displayOutOfRange();
  }

  delay(1000); // Esperar antes de la siguiente medición
}
