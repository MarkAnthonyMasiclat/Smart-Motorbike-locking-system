#include <HX711.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <WiFi.h>
#include <PubSubClient.h>

// HX711 pins
#define DOUT  2
#define CLK   3
HX711 scale;

// Servo pins
#define SERVO1_PIN  8
#define SERVO2_PIN  9
Servo servo1;
Servo servo2;

// LED & Buzzer
#define LED_PIN    13
#define BUZZER_PIN 7

// LCD
LiquidCrystal_I2C lcd(0x27,16,2);

// Wi-Fi and MQTT
const char* ssid = "WiFi";
const char* password = "12345678";
const char* mqtt_server = "000.00.00.00";
WiFiClient espClient;
PubSubClient client(espClient);

// System states
enum SystemState { UNLOCKED, LOCKED, ALARM };
SystemState state = UNLOCKED;

// Calibration and thresholds
float lockedWeight = 0.0;
float weightTolerance = 0.05;  // kg tolerance for small-scale test
float bikeThreshold = 0.2;     // kg minimum weight to trigger lock
float calibrationFactor = 145000; // HX711 factor from previous calibration

// Alarm timing
unsigned long lastFlash = 0;
bool alarmState = false;

// Weight stabilization
unsigned long weightStableStart = 0;
bool weightStable = false;
const unsigned long stableTime = 2000; // 2 seconds

void setup() {
  Serial.begin(9600);

  // Initialize HX711
  scale.begin(DOUT, CLK);
  scale.set_scale(calibrationFactor);
  scale.tare();

  // Initialize Servos
  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  servo1.write(0); // Open
  servo2.write(0); // Open

  // LED & Buzzer
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("UNLOCKED");

  // Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  // MQTT
  client.setServer(mqtt_server, 1883);
  client.setCallback(mqttCallback);
}

void loop() {
  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop();

  float weight = scale.get_units();
  Serial.println(weight);

  unsigned long now = millis();

  // --- Weight stabilization logic ---
  if(state == UNLOCKED){
    if(weight > bikeThreshold){
      if(!weightStable){
        weightStableStart = millis();
        weightStable = true;
      } else if(now - weightStableStart >= stableTime){
        lockedWeight = weight;
        closeServos();
        lcdMessage("LOCKED");
        state = LOCKED;
        weightStable = false; // reset
      }
    } else {
      weightStable = false; // reset if weight drops below threshold
    }
  }

  switch(state){
    case LOCKED:
      if(abs(weight - lockedWeight) > weightTolerance){
        state = ALARM;
        lcdMessage("ALARM");
      }
      break;

    case ALARM:
      // Non-blocking alarm flash
      if(now - lastFlash > 500){ // 500 ms toggle
        alarmState = !alarmState;
        digitalWrite(LED_PIN, alarmState);
        if(alarmState){
          tone(BUZZER_PIN, 1000); // 1000 Hz tone ON
        } else {
          noTone(BUZZER_PIN);     // tone OFF
        }
        lastFlash = now;
      }
      break;
  }
}

void closeServos(){
  servo1.write(100); // Adjust as needed
  servo2.write(90);
}

void openServos(){
  servo1.write(0);
  servo2.write(0);
}

void stopAlarm(){
  digitalWrite(LED_PIN,LOW);
  noTone(BUZZER_PIN);
  lcdMessage("UNLOCKED");
  state = UNLOCKED;
}

void lcdMessage(String msg){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(msg);
}

// MQTT callback
void mqttCallback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for(unsigned int i = 0; i < length; i++){
    message += (char)payload[i];
  }

  if(message == "release"){
    openServos();
    stopAlarm();
  }
}

void reconnectMQTT() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ArduinoBikeLock")) {
      Serial.println("connected");
      client.subscribe("bike/lock"); // your topic
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      delay(2000);
    }
  }
}