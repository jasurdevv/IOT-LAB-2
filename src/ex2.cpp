#include "Arduino.h"

const uint8_t LIGHT_SENSOR_PIN = 33;
const unsigned long SAMPLE_PERIOD_MS = 1000;
const uint8_t SAMPLES_PER_BURST = 10;
unsigned long previousSampleMs = 0;

struct LightStats {
	int minValue;
	int maxValue;
	long total;
};

static LightStats readLightBurst(void)
{
	LightStats stats = {4095, 0, 0};
	for (uint8_t i = 0; i < SAMPLES_PER_BURST; ++i) {
		const int value = analogRead(LIGHT_SENSOR_PIN);
		stats.minValue = min(stats.minValue, value);
		stats.maxValue = max(stats.maxValue, value);
		stats.total += value;
	}
	return stats;
}

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
	if (currentMs - previousSampleMs < SAMPLE_PERIOD_MS) {
		return;
	}
	previousSampleMs = currentMs;

	const LightStats stats = readLightBurst();

	Serial.print("min=");
	Serial.print(stats.minValue);
	Serial.print(" max=");
	Serial.print(stats.maxValue);
	Serial.print(" avg=");
	Serial.println(stats.total / SAMPLES_PER_BURST);
}
