#include <Arduino.h>
#include "wifiSetup.h"
#include "bmp280.h"
#include "distance.h"
#include "flame.h"
#include "ledRGB.h"
#include "buzzer.h"
#include "button.h"  
#include "blynkSetup.h"
#include "blynkConfig.h" // Asegura macros BLYNK_TEMPLATE_ID/NAME/AUTH disponibles aquí
#include "googleSheets.h"

// Configuración WiFi y Blynk
char ssid[] = "Nandez";
char password[] = "pendejo8";
// Auth Token ahora se obtiene de define BLYNK_AUTH_TOKEN (ver blynkConfig.h)

// URL de Google Apps Script (reemplazar con tu deployment URL)
const char* googleScriptUrl = "https://script.google.com/macros/s/AKfycbzBkxII56YZ73sTPBUxR9V55go09jxexB0K1m7-C9POzfuSrTZwB60CDYr6wjia8MJN/exec";

// Variables para control de temperatura

float baselineTemp = 0; // Temperatura inicial de referencia
bool baselineTempSet = false; // Indica si la temperatura base ha sido establecida
const float TEMP_THRESHOLD = 3.0;  // Variación de temperatura en °C para activar alarma

// Variables para control de distancia
const float DISTANCE_THRESHOLD = 30.0;  // Distancia en cm para activar alarma

// Variables de tiempo para lecturas

unsigned long lastReadTime = 0; // Última vez que se leyeron los sensores
const unsigned long READ_INTERVAL = 1000;  // Leer cada 1 segundo

unsigned long lastGoogleSheetsTime = 0; // Última vez que se envió a Google Sheets
const unsigned long GOOGLE_SHEETS_INTERVAL = 60000;  // Enviar cada 60 segundos (evitar límites de cuota)

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
  setupWiFi(ssid, password);
  // Blynk setup (usa la conexión WiFi existente)
  setupBlynk(BLYNK_AUTH_TOKEN);
  // Google Sheets setup
  setupGoogleSheets(googleScriptUrl);
  
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
  // Blynk loop
  blynkRun();
  blynkEnsureConnected(); // Intentar reconectar si se perdió conexión
  
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
    bool ledIsRed = (tempAlarm || distanceAlarm);
    if (ledIsRed) setLEDColor(LED_RED); else setLEDColor(LED_GREEN);
    
    // Control del Buzzer (flama O petición desde Blynk)
    if (flameDetected || isBlynkBuzzerRequested()) {
      buzzerOn();
      Serial.println(">>> ¡¡¡FUEGO DETECTADO!!! <<<");
    } else {
      buzzerOff();
    }

    // Publicar a Blynk (debug de estado de conexión)
    if (!blynkIsConnected()) {
      Serial.println("[Blynk] Aún sin conexión. Datos locales OK.");
    }
    blynkPublish(temperature, pressure, altitude, distance, flameDetected, ledIsRed);
    
    Serial.println("========================================\n");
  }
  
  // Enviar a Google Sheets cada 60 segundos
  if (millis() - lastGoogleSheetsTime >= GOOGLE_SHEETS_INTERVAL) {
    lastGoogleSheetsTime = millis();
    
    // Leer valores actuales
    float temp = readTemperature();
    float pres = readPressure();
    float alt = readAltitude();
    float dist = readDistance();
    bool flame = isFlameDetected();
    
    Serial.println("[GoogleSheets] Enviando datos periódicos...");
    if (sendToGoogleSheets(temp, pres, alt, dist, flame)) {
      Serial.println("[GoogleSheets] ✓ Datos enviados exitosamente");
    } else {
      Serial.println("[GoogleSheets] ✗ Error al enviar datos");
    }
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
