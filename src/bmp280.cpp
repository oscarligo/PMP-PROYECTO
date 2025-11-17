#include "bmp280.h"
#include <Wire.h>
#include <Adafruit_BMP280.h>

// Pines I2C para ESP8266
#define BMP_SDA 4  // D2 (GPIO4)
#define BMP_SCL 5  // D1 (GPIO5)

Adafruit_BMP280 bmp;

bool setupBMP280() {
  // Inicializar I2C con los pines específicos
    Wire.begin(BMP_SDA, BMP_SCL);

  if (!bmp.begin(0x76)) {  // Dirección I2C típica del BMP280
    Serial.println("No se pudo encontrar el sensor BMP280!");
    return false;
    }

  // Configuración del sensor
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     // Modo de operación
                  Adafruit_BMP280::SAMPLING_X2,     // Temp. oversampling
                  Adafruit_BMP280::SAMPLING_X16,    // Pressure oversampling
                  Adafruit_BMP280::FILTER_X16,      // Filtering
                  Adafruit_BMP280::STANDBY_MS_500); // Standby time

    Serial.println("BMP280 inicializado correctamente");
    return true;
}

float readTemperature() {
    return bmp.readTemperature();
}

float readPressure() {
    return bmp.readPressure() / 100.0F;  // Convertir a hPa
}

float readAltitude() {
    return bmp.readAltitude(1013.25);  // Presión a nivel del mar en hPa
}
