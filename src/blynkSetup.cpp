#define BLYNK_PRINT Serial  // Activar mensajes de debug de Blynk
#include "blynkSetup.h"
#include "blynkConfig.h" // Debe ir antes de incluir Blynk

#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#include "buzzer.h"

// Store auth token
typedef struct {
  const char* auth;
} BlynkConfig;

static BlynkConfig g_cfg = { nullptr };
static bool g_blynkBuzzerOn = false; // remote buzzer request

// Forward declarations for Blynk handlers
BLYNK_CONNECTED() {
  // Sync app state on connect (e.g., button V6)
  Blynk.syncVirtual(V6);
}

BLYNK_WRITE(V6) {
  int val = param.asInt();
  g_blynkBuzzerOn = (val == 1);
  // Do not directly force buzzer here; main will combine logic (flame OR remote)
}

void setupBlynk(const char* authToken) {
  g_cfg.auth = authToken; // normalmente BLYNK_AUTH_TOKEN
  Blynk.config(g_cfg.auth);
  Blynk.connect(5000);
  Serial.println("Blynk configurado. Intentando conexión inicial...");
}

void blynkRun() {
  Blynk.run();
}

void blynkEnsureConnected() {
  static unsigned long lastAttempt = 0;
  const unsigned long RECONNECT_INTERVAL = 10000; // 10s
  if (Blynk.connected()) return;
  unsigned long now = millis();
  if (now - lastAttempt >= RECONNECT_INTERVAL) {
    Serial.println("[Blynk] Desconectado. Reintentando conexión...");
    Blynk.connect();
    lastAttempt = now;
  }
}

bool blynkIsConnected() {
  return Blynk.connected();
}

void blynkPublish(float temperature, float pressure, float altitude,
                  float distance, bool flameDetected, bool ledIsRed) {
  if (!Blynk.connected()) {
    // Debug mínimo; evitar spam
    static unsigned long lastMsg = 0; 
    if (millis() - lastMsg > 5000) {
      Serial.println("[Blynk] No conectado. No se envían datos.");
      lastMsg = millis();
    }
    return;
  }
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, pressure);
  Blynk.virtualWrite(V2, altitude);
  Blynk.virtualWrite(V3, distance > 0 ? distance : 0);
  Blynk.virtualWrite(V4, flameDetected ? 1 : 0);
  Blynk.virtualWrite(V5, ledIsRed ? 1 : 0);
}

bool isBlynkBuzzerRequested() {
  return g_blynkBuzzerOn;
}
