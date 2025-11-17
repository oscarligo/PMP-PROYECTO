#include "googleSheets.h"
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

static String g_scriptUrl = "";

void setupGoogleSheets(const char* scriptUrl) {
    g_scriptUrl = String(scriptUrl);
    Serial.println("Google Sheets configurado");
    Serial.print("URL: ");
    Serial.println(g_scriptUrl);
}

bool sendToGoogleSheets(float temperature, float pressure, float altitude,
                        float distance, bool flameDetected) {
    if (g_scriptUrl.length() == 0) {
        Serial.println("[GoogleSheets] Error: URL no configurada");
        return false;
    }

    // Crear cliente HTTPS (Google Apps Script usa HTTPS)
    WiFiClientSecure client;
    client.setInsecure(); // No validar certificado (simplifica para pruebas)

    HTTPClient http;

    // Construir URL con parámetros
    String url = g_scriptUrl;
    url += "?temperature=" + String(temperature, 2);
    url += "&pressure=" + String(pressure, 2);
    url += "&altitude=" + String(altitude, 2);
    url += "&distance=" + String(distance, 2);
    url += "&flame=" + String(flameDetected ? "SI" : "NO");

    Serial.println("[GoogleSheets] Enviando datos...");
    Serial.println("URL: " + url);

    http.begin(client, url);
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS); // Seguir redirects de Google

    int httpCode = http.GET();

    if (httpCode > 0) {
        Serial.print("[GoogleSheets] Código HTTP: ");
        Serial.println(httpCode);
        
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY || httpCode == HTTP_CODE_FOUND) {
        String payload = http.getString();
        Serial.println("[GoogleSheets] Respuesta: " + payload);
        http.end();
        return true;
        }
    } else {
        Serial.print("[GoogleSheets] Error en petición: ");
        Serial.println(http.errorToString(httpCode));
    }

    http.end();
    return false;
}
