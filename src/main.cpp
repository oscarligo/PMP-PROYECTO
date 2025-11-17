#include <Arduino.h>
#include "wifiSetup.h"
#include "bmp280.h"
#include "distance.h"
#include "flame.h"
#include "ledRGB.h"
#include "buzzer.h"
#include "button.h"  

// Configuración WiFi 

char ssid[] = "SSID";
char password[] = "Password";


// Variables para control de temperatura

float baselineTemp = 0; // Temperatura inicial de referencia
bool baselineTempSet = false; // Indica si la temperatura base ha sido establecida
const float TEMP_THRESHOLD = 3.0;  // Variación de temperatura en °C para activar alarma

// Variables para control de distancia
const float DISTANCE_THRESHOLD = 30.0;  // Distancia en cm para activar alarma

// Variables de tiempo para lecturas

unsigned long lastReadTime = 0; // Última vez que se leyeron los sensores
const unsigned long READ_INTERVAL = 1000;  // Leer cada 1 segundo

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println("\n\n=== Iniciando sistema de sensores ===");
  
  // Inicializar todos los módulos
  setupLED();
  setupBuzzer();
  setupButton();
  setupDistance();
  setupFlame();
  
  // Inicializar BMP280
  if (!setupBMP280()) {
    Serial.println("ERROR: No se pudo inicializar el BMP280");
    // Hacer parpadear LED rojo para indicar error
    for(int i = 0; i < 5; i++) {
      setLEDColor(LED_RED);
      delay(200);
      setLEDColor(LED_OFF);
      delay(200);
    }
  }
  
  // WiFi setup 
  // setupWiFi(ssid, password);
  
  // Obtener temperatura base después de 2 segundos
  delay(2000);
  baselineTemp = readTemperature();
  baselineTempSet = true;
  
  Serial.println("\n=== Sistema listo ===");
  Serial.println("LED Verde = Estado normal");
  Serial.println("LED Rojo = Temperatura alta o proximidad detectada");
  Serial.println("Buzzer = Fuego detectado\n");
}

void loop() {
  
  // Verificar si es tiempo de leer sensores
  if (millis() - lastReadTime >= READ_INTERVAL) {
    lastReadTime = millis();
    
    // Variables de alarma
    bool tempAlarm = false;
    bool distanceAlarm = false;
    
    // ===== LEER SENSORES =====
    
    // Leer BMP280 (temperatura y presión)
    float temperature = readTemperature();
    float pressure = readPressure();
    float altitude = readAltitude();
    
    // Leer distancia
    float distance = readDistance();
    
    // Leer sensor de flama
    bool flameDetected = isFlameDetected();
    
    // ===== IMPRIMIR RESULTADOS =====
    Serial.println("========================================");
    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.println(" °C");
    
    Serial.print("Presión: ");
    Serial.print(pressure);
    Serial.println(" hPa");
    
    Serial.print("Altitud: ");
    Serial.print(altitude);
    Serial.println(" m");
    
    Serial.print("Distancia: ");
    if (distance > 0) {
      Serial.print(distance);
      Serial.println(" cm");
    } else {
      Serial.println("No hay objeto detectado");
    }
    
    Serial.print("Flama: ");
    Serial.println(flameDetected ? "DETECTADA!" : "No detectada");
    
    // ===== CONTROL DE ACTUADORES =====
    
    // Verificar variación de temperatura
    if (baselineTempSet && abs(temperature - baselineTemp) > TEMP_THRESHOLD) {
      tempAlarm = true;
      Serial.print("¡ALERTA! Variación de temperatura: ");
      Serial.print(abs(temperature - baselineTemp));
      Serial.println(" °C");
    }
    
    // Verificar proximidad
    if (distance > 0 && distance < DISTANCE_THRESHOLD) {
      distanceAlarm = true;
      Serial.print("¡ALERTA! Objeto cercano a ");
      Serial.print(distance);
      Serial.println(" cm");
    }
    
    // Control del LED RGB
    if (tempAlarm || distanceAlarm) {
      setLEDColor(LED_RED);
    } else {
      setLEDColor(LED_GREEN);
    }
    
    // Control del Buzzer (solo si hay flama)
    if (flameDetected) {
      buzzerOn();
      Serial.println(">>> ¡¡¡FUEGO DETECTADO!!! <<<");
    } else {
      buzzerOff();
    }
    
    Serial.println("========================================\n");
  }
  
  // Verificar botón (ejemplo de uso - resetear la temperatura base)
  if (buttonPressedDebounce()) {
    baselineTemp = readTemperature();
    Serial.println(">>> Temperatura base actualizada <<<");
    buzzerBeep(100);  // Confirmación auditiva
  }
  
  // Pequeña pausa para no saturar el procesador
  delay(10);
}
