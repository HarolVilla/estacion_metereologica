#include <Wire.h>
#include <WiFi.h>
#include <HTTPClient.h>


#include <Adafruit_AHTX0.h>
#include <Adafruit_BMP280.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#include <WebServer.h>

WebServer server(80);

// WIFI
const char* ssid = "xxxxxxxxx"; ///conexion a wifi
const char* password = "xxxxxxxxx"; // pass del wifi

// Google Script
const char* serverName = "url del  google drive"; // aqui tienes que poner la direccion que te da el google drive de tu excel

// Sensores
Adafruit_AHTX0 aht;
Adafruit_BMP280 bmp;

// Variables
float temp_bmp, temp_aht, hum, pres;

unsigned long lastTime = 0;
unsigned long interval = 60000; // cada cuanto envia los datos en milisegundos

unsigned long lastDisplay = 0;
unsigned long displayInterval = 2000; // actualizacion pantalla cada 2 segundos

void handleRoot() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
body {
  font-family: Arial;
  text-align: center;
  background: #0f172a;
  color: white;
}
.card {
  background: #1e293b;
  margin: 15px;
  padding: 20px;
  border-radius: 15px;
  font-size: 22px;
}
h1 { color: #38bdf8; }
</style>
</head>
<body>

<h1>🌍 Estacion Casa Harol</h1> 

<div class="card">🌡 Temp AHT: )rawliteral" + String(temp_aht) + R"rawliteral( °C</div>
<div class="card">🌡 Temp BMP: )rawliteral" + String(temp_bmp) + R"rawliteral( °C</div>
<div class="card">💧 Humedad: )rawliteral" + String(hum) + R"rawliteral( %</div>
<div class="card">🌬 Presion: )rawliteral" + String(pres) + R"rawliteral( hPa</div>

</body>
</html>
)rawliteral";

  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(100000);  

  // AHT20
  if (!aht.begin()) {
    Serial.println("❌ Error AHT20");
    while (1);
  }

  // BMP280
  if (!bmp.begin(0x77)) {
    Serial.println("❌ Error BMP280");
    while (1);
  }
  // OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("❌ Error OLED");
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  // WiFi
  WiFi.begin(ssid, password);
  Serial.print("Conectando WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  server.on("/", handleRoot);
  server.begin();

  Serial.println("Servidor web iniciado");
  Serial.print("Abre en navegador: http://");
  Serial.println(WiFi.localIP());

  Serial.println("\n✅ WiFi conectado");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  
server.handleClient();

  // 🔹 Pantalla (cada 2 segundos)
  if (millis() - lastDisplay > displayInterval) {
    lastDisplay = millis();

    leerSensores();
    mostrarOLED();
  }

  // 🔹 Envío a Google (cada 5 minutos)
  if (millis() - lastTime > interval) {
    lastTime = millis();

    mostrarDatos();
    enviarDatos();
  }
}
void leerSensores() {
  sensors_event_t humidity_event, temp_event;
  aht.getEvent(&humidity_event, &temp_event);

  temp_aht = temp_event.temperature;
  hum = humidity_event.relative_humidity;

  temp_bmp = bmp.readTemperature();
  pres = bmp.readPressure() / 100.0; // hPa
}

void mostrarDatos() {
  Serial.println("=========== MEDICIÓN ===========");

  Serial.print("🌡 Temperatura AHT20: ");
  Serial.print(temp_aht);
  Serial.println(" °C");

  Serial.print("🌡 Temperatura BMP280: ");
  Serial.print(temp_bmp);
  Serial.println(" °C");

  Serial.print("💧 Humedad: ");
  Serial.print(hum);
  Serial.println(" %");

  Serial.print("🌬 Presión: ");
  Serial.print(pres);
  Serial.println(" hPa");

  Serial.println("================================");
}

void mostrarOLED() {
  display.clearDisplay();

  display.setCursor(0, 0);
  display.print("TEMP AHT: ");
  display.print(temp_aht);
  display.println(" C");

  display.print("TEMP BMP: ");
  display.print(temp_bmp);
  display.println(" C");

  display.print("HUM: ");
  display.print(hum);
  display.println(" %");

  display.print("PRES: ");
  display.print(pres);
  display.println(" hPa");

  display.display();
}
void enviarDatos() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");
    
    String json = "{";
    json += "\"temp_bmp\":" + String(temp_bmp) + ",";
    json += "\"temp_aht\":" + String(temp_aht) + ",";
    json += "\"hum\":" + String(hum) + ",";
    json += "\"pres\":" + String(pres);
    json += "}";

    int httpResponseCode = http.POST(json);

    Serial.print("📡 Envío a Google Sheets → Código: ");
    Serial.println(httpResponseCode);

    http.end();
  } else {
    Serial.println("❌ WiFi desconectado");
  }

}