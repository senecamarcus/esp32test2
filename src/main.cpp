#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SDA_PIN 21
#define SCL_PIN 22
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);  // Initialize serial communication
  Wire.begin(SDA_PIN, SCL_PIN); // Initialize I2C communication
  
  if (!display.begin(SCREEN_ADDRESS)) {
    Serial.println(F("Error inicializando la pantalla OLED"));
    for (;;);
  }

  Serial.println(F("OLED display initialized successfully"));
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("¡Hola, ESP32!");
  display.display();
  delay(2000);
  display.clearDisplay();
}
