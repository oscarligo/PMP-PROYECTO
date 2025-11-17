#ifndef GOOGLE_SHEETS_H
#define GOOGLE_SHEETS_H

#include <Arduino.h>

// Configurar la URL del Google Apps Script (Web App deployment URL)
void setupGoogleSheets(const char* scriptUrl);

// Enviar datos a Google Sheets
// Retorna true si el envío fue exitoso
bool sendToGoogleSheets(float temperature, float pressure, float altitude,
                        float distance, bool flameDetected);

#endif // GOOGLE_SHEETS_H
