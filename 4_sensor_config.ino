#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "DHT.h"

#define DHTTYPE DHT11
#define DHTPin D4   // Changed to D4
#define ON_Board_LED 2

#define TRIG_PIN D2  // Trigger pin for Ultrasonic Sensor
#define ECHO_PIN D1  // Echo pin for Ultrasonic Sensor
#define BUZZER_PIN D3 // Buzzer pin
#define THRESHOLD 35   // Distance threshold in cm

const char* ssid = "Shetty's";
const char* password = "samshetty";

const char* host = "script.google.com";
const int httpsPort = 443;

WiFiClientSecure client;
DHT dht(DHTPin, DHTTYPE);

String GAS_ID = "AKfycbxNhoKwhgf9gc2t2T7Zt6Q09XoQDBAcTP46KoRe4hO2lqpXIleL6XoPU4bA84vzslZf";

unsigned long lastDataSendTime = 0;
const unsigned long dataSendInterval = 5000; // 5 seconds

void setup() {
    Serial.begin(115200);
    delay(500);
    dht.begin();
    delay(500);

    WiFi.begin(ssid, password);
    Serial.println("Connecting to WiFi");

    pinMode(ON_Board_LED, OUTPUT);
    digitalWrite(ON_Board_LED, HIGH);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);

    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        digitalWrite(ON_Board_LED, LOW);
        delay(250);
        digitalWrite(ON_Board_LED, HIGH);
        delay(250);
    }

    digitalWrite(ON_Board_LED, HIGH);
    Serial.println("\nSuccessfully connected to WiFi");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    client.setInsecure();
}

void loop() {
    checkDistance(); // Runs Ultrasonic Sensor Continuously
    
    if (millis() - lastDataSendTime >= dataSendInterval) {
        sendSensorData();
        lastDataSendTime = millis();
    }
}

void checkDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH);
    float distance = (duration * 0.0343) / 2;

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance > 0 && distance <= THRESHOLD) {
        digitalWrite(BUZZER_PIN, HIGH);
    } else {
        digitalWrite(BUZZER_PIN, LOW);
    }
}

void sendSensorData() {
    int ground = analogRead(A0);
    int h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    Serial.print("Temperature: "); Serial.println(t);
    Serial.print("Humidity: "); Serial.println(h);
    Serial.print("Ground Sensor: "); Serial.println(ground);

    Serial.println("==========");
    Serial.print("Connecting to: ");
    Serial.println(host);

    if (!client.connect(host, httpsPort)) {
        Serial.println("Connection failed");
        return;
    }

    String url = "/macros/s/" + GAS_ID + "/exec?temperature=" + String(t) + "&humidity=" + String(h) + "&Ground=" + String(ground);
    Serial.print("Requesting URL: ");
    Serial.println(url);

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "User-Agent: ESP8266Client\r\n" +
                 "Connection: close\r\n\r\n");

    Serial.println("Request sent");

    while (client.connected()) {
        String line = client.readStringUntil('\n');
        if (line == "\r") {
            Serial.println("Headers received");
            break;
        }
    }

    String line = client.readStringUntil('\n');
    if (line.startsWith("{\"state\":\"success\"")) {
        Serial.println("ESP8266/Arduino CI successful!");
    } else {
        Serial.println("ESP8266/Arduino CI failed");
    }

    Serial.print("Reply: ");
    Serial.println(line);
    Serial.println("Closing connection");
    Serial.println("==========");
}
