#include "Arduino.h"

const uint8_t LIGHT_SENSOR_PIN = 33;
const unsigned long POLL_PERIOD_MS = 300;
const int ALERT_ON_LEVEL = 3000;
const int ALERT_OFF_LEVEL = 2500;
unsigned long previousPollMs = 0;
bool isAlert = false;

/****************************************************/
void setup(void)
{
	Serial.begin(115200);
	pinMode(LIGHT_SENSOR_PIN, INPUT);
}


/****************************************************/
void loop(void)
{
	const unsigned long currentMs = millis();
	if (currentMs - previousPollMs < POLL_PERIOD_MS) {
		return;
	}
	previousPollMs = currentMs;

	const int level = analogRead(LIGHT_SENSOR_PIN);
	const bool shouldRaise = !isAlert && level > ALERT_ON_LEVEL;
	const bool shouldClear = isAlert && level < ALERT_OFF_LEVEL;

	if (shouldRaise || shouldClear) {
		isAlert = shouldRaise;
		Serial.println(isAlert ? "ALERT=1" : "ALERT=0");
	}
}
