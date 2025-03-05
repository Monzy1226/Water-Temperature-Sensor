#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Pin Definitions
#define DS18B20_PIN 19  // DS18B20 data pin (P19)
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  // Reset pin (not used)
#define SDA_PIN 21  // SDA (I2C) -> P21
#define SCL_PIN 22  // SCL (I2C) -> P22

// Setup DS18B20 Sensor
OneWire oneWire(DS18B20_PIN);
DallasTemperature sensors(&oneWire);

// Setup OLED Display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
    Serial.begin(115200);

    // Start DS18B20 Sensor
    sensors.begin();

    // Start OLED Display
    Wire.begin(SDA_PIN, SCL_PIN);  // Initialize I2C with custom pins
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // 0x3C is the default OLED I2C address
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
}

void loop() {
    sensors.requestTemperatures();  // Get temperature from DS18B20
    float tempC = sensors.getTempCByIndex(0);  // Read temperature in Celsius

    // Print to Serial Monitor
    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.println(" °C");

    // Display Temperature on OLED
    display.clearDisplay();
    display.setCursor(10, 20);
    display.print("Temp: ");
    display.print(tempC);
    display.print(" C");
    display.display();

    delay(1000);  // Wait 1 second before next reading
}
