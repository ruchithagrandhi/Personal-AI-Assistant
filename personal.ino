#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <Servo.h>
#include <SoftwareSerial.h>

#define SOUND_SENSOR_PIN A0  
#define SERVO_PIN 9         
Servo myServo;

const char* ssid = "Ruchitha";    
const char* password = "22kt1a0504"; 

void setup() {
  Serial.begin(115200);
  myServo.attach(SERVO_PIN);  
  myServo.write(0);           
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  int soundValue = analogRead(SOUND_SENSOR_PIN); 
  if (soundValue > 500) { 
    myServo.write(90);    
    delay(1000);          
    myServo.write(0);     
    sendGoogleCommand("What is the time?"); 
    delay(2000); 
  }
  delay(100); 
}

void sendGoogleCommand(String command) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    String url = "http://GOOGLE_ASSISTANT_API_ENDPOINT"; 
    http.begin(client, url);
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.POST("{\"command\":\"" + command + "\"}");
    if (httpCode == 200) {
      String payload = http.getString();
      Serial.println(payload);
    }
    http.end();
  }
}