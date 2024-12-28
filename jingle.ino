#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <Adafruit_NeoPixel.h>

#define AUDIO_PIN D6

const char* _SSID = "MCS_Guest";
const char* _SSID_PASSWORD = "";
const char* _FIREBASE_URL = "https://doorbell-338a5-default-rtdb.firebaseio.com/ALERT.json";

// Setup //

void setup() {
    Serial.begin(115200);
}

// Loop //

const unsigned long TIMER_INTERVAL = 1000;
unsigned long apex_time = 0;
bool buzz = false;

void loop() {
	unsigned long delta_time = millis();

	if (delta_time - apex_time >= TIMER_INTERVAL) {
		apex_time = delta_time;
		buzz = !buzz;

		if (buzz == true) {
			tone(AUDIO_PIN, 3000, TIMER_INTERVAL);
		}
	}
}
