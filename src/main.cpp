#include <U8g2lib.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>

// Recordar agregar usuario y clave de wifi para actualizar el codigo.
const char *ssid = "*********";
const char *password = "+++++++++";

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_ADDRESS 0x3C
#define time_delay 15000

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

// Function declaration
void getBitcoinPrice();
void connectToWiFi();

void setup() {
  Wire.begin();
  u8g2.begin();

  // Connect to WiFi
  connectToWiFi();

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 16, "Hello, Santiago!");
  u8g2.sendBuffer();
  delay(time_delay);
}

void loop() {
  getBitcoinPrice();
  delay(time_delay);  // Wait 15 seconds before updating the price
}

void connectToWiFi() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");
}

void getBitcoinPrice() {
  HTTPClient http;
  http.begin("https://api.coingecko.com/api/v3/simple/price?ids=bitcoin&vs_currencies=usd");

  int httpCode = http.GET();

  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);

    // Extract Bitcoin price from JSON
    float bitcoinPrice = doc["bitcoin"]["usd"];

    // Display Bitcoin price on OLED
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.setCursor(0, 16);
    u8g2.print("Bitcoin Price: $");
    u8g2.print(bitcoinPrice, 2);  // Display two decimal places
    u8g2.sendBuffer();
  }

  http.end();
}
