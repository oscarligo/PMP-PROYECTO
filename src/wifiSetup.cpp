#include "wifiSetup.h"
#include <ESP8266WiFi.h>  

void setupWiFi( char ssid[],  char password[]) {
    delay (100);
    Serial.begin(115200);
    Serial.print("\nConnecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    randomSeed(micros());

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

}