#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>
#include <HX711.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define BMP_SDA_PIN 21
#define BMP_SCL_PIN 22
#define LED_VERMELHO_PIN 13
#define LOADCELL_DOUT_PIN 23
#define LOADCELL_SCK_PIN 19
#define SERVO_PIN 18
#define TARGET_WEIGHT 30 // Peso alvo em gramas

Adafruit_BMP085 bmp;
HX711 scale;
Servo servo;
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

const char* ssid = "Casa_celebrar1_5G"; 
const char* password = "ML010122";
const char* mqttBroker = "localhost"; 
const int mqttPort = 1883; 

void setup() {
  Serial.begin(9600);
  pinMode(LED_VERMELHO_PIN, OUTPUT);
  servo.attach(SERVO_PIN);

  Wire.begin(BMP_SDA_PIN, BMP_SCL_PIN);
  if (!bmp.begin()) {
    Serial.println("Não foi possível iniciar o sensor BMP180!");
    while (1);
  }

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(1); 
  scale.tare(); 

  connectWiFi();
  mqttClient.setServer(mqttBroker, mqttPort);
}

void loop() {
  if (!mqttClient.connected()) {
    reconnectMQTT();
  }
  
  mqttClient.loop();

  float temperature = bmp.readTemperature();
  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.println(" °C");

  float weight = scale.get_units(); 
  Serial.print("Peso: ");
  Serial.print(weight);
  Serial.println(" g");

  if (temperature > 40 || temperature < 37) {
    digitalWrite(LED_VERMELHO_PIN, HIGH); // Acender o LED vermelho
    mqttClient.publish("meu_topico/temperatura", String(temperature).c_str(), true);
  } else {
    digitalWrite(LED_VERMELHO_PIN, LOW); // Apagar o LED vermelho
  }

  if (weight < TARGET_WEIGHT) {
    servo.write(90); // Posição para soltar mais ração
    delay(1000); // Aguardar 1 segundo
    servo.write(0); // Posição inicial
    mqttClient.publish("meu_topico/peso", String(weight).c_str(), true);
  }

  delay(1000); // Aguardar 1 segundo antes de verificar novamente
}

void connectWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Conectando à rede Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Conectado à rede Wi-Fi");
}

void reconnectMQTT() {
  while (!mqttClient.connected()) {
    Serial.print("Conectando ao broker MQTT...");
    if (mqttClient.connect("ESP32_Client")) {
      Serial.println("Conectado ao broker MQTT");
    } else {
      Serial.print("Falha na conexão, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" Tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}
