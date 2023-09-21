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
  delay(2000);
  display.clearDisplay();
  display.display();
}

void displayTimeOfFlight(double duration) {
  display.clearDisplay();
  display.setTextSize(1.8);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 15);
  display.print("Tiempo de Vuelo:");
  display.setTextSize(3.5);
  display.setCursor(10, 40);
  display.print(duration, 1);
  display.print(" ps");
  display.display();
}

void loop() {
  VL53L0X_RangingMeasurementData_t medida;

  // Limpiar la pantalla y prepararse para nuevos datos
  display.clearDisplay();
  display.setTextSize(1.5);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Midiendo Tiempo...");
  display.display();

  // Realizar la prueba de rango
  lox.rangingTest(&medida, false);

  // Calcular el tiempo de vuelo en picosegundos
  double duration = medida.RangeMilliMeter * 2.0 * 3.335640952;

  // Mostrar resultado del tiempo de vuelo
  if (medida.RangeStatus != 4) {
    displayTimeOfFlight(duration);
    Serial.print("Tiempo de Vuelo: "); Serial.print(duration, 1); Serial.println(" ps");
  } else {
    display.clearDisplay();
    display.setTextSize(1.8);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(15, 15);
    display.println("Fuera de Rango");
    display.display();
  }

  delay(1000);
}
