#include "ESP32Utils.h"

#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOTA.h>

ESP32Utils::ESP32Utils(){

}

void ESP32Utils::initWiFi(char* ssid, char* password)
{
  Serial.print("Conectando à rede: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    Serial.print("|");
    delay(200);
  }

  Serial.println();
  Serial.println("Conectado com sucesso.");
}

void ESP32Utils::initOTA(){
  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else
        type = "filesystem";
      Serial.println("Iniciando atualizacao " + type);
    })
    .onEnd([]() {
      Serial.println("\nFinalizado");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Carregando: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Erro[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Falha de autenticação");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Falha na inicialização");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Falha na conexão");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Falha na resposta");
      else if (error == OTA_END_ERROR) Serial.println("Falha final");
    });

  ArduinoOTA.begin();

  Serial.println("Pronto");
  Serial.print("IP da ESP: ");
  Serial.println(WiFi.localIP());
}
