#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define TX2 17
#define RX2 16 
#define BMP_SDA 21
#define BMP_SCL 22

Adafruit_BMP280 bmp; 
String URL = "http://192.168.8.100/thermistor/data_text.php";
const char* ssid = "Dialog 4G dush";
const char* password = "dush@shamod";

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RX2, TX2);
  connectWiFi();
  Wire.begin(BMP_SDA, BMP_SCL);
  if (!bmp.begin(0x76)) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,    
                  Adafruit_BMP280::SAMPLING_X2,    
                  Adafruit_BMP280::SAMPLING_X16,    
                  Adafruit_BMP280::FILTER_X16,    
                  Adafruit_BMP280::STANDBY_MS_500); 
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }

  if (Serial2.available() > 0) {
    float temperature = Serial2.readStringUntil('\n').toFloat(); // Read temperature from Serial2 until newline character

    HTTPClient http;
    http.begin(URL);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    float RoomTemperature = bmp.readTemperature();
    float RoomPressure = bmp.readPressure();

    String postData = "temperature=" + String(temperature) +                  
                      "&RoomTemperature=" + String(RoomTemperature) +
                      "&RoomPressure=" + String(RoomPressure);

    int httpCode = http.POST(postData);

    if (httpCode > 0) {
      
      String payload = http.getString();
    } else {
    
      Serial.print("HTTP request failed with error code: "); Serial.println(httpCode);
    }

    Serial.print("Data: "); Serial.println(postData);
    Serial.print("httpCode: "); Serial.println(httpCode);
  }
}

void connectWiFi() {
  WiFi.mode(WIFI_OFF);
  delay(50);
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 10) {
    delay(50);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to WiFi");
    Serial.print("IP address: "); Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFailed to connect to WiFi. Please check your credentials or network.");
  }
}
