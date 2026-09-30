#include "Arduino.h"

const uint8_t BUTTON_PIN = 25;
const uint8_t ledPins[] = {26, 27, 12, 14};
const uint8_t LED_COUNT = sizeof(ledPins) / sizeof(ledPins[0]);
const uint8_t MAX_COUNT_WRAP = LED_COUNT + 1;
const unsigned long DEBOUNCE_MS = 30;

uint8_t counter = 0;
int previousReading = LOW;
int debouncedState = LOW;
unsigned long lastChangeMs = 0;

static void showCounterOnLeds(uint8_t value)
{
	for (uint8_t i = 0; i < LED_COUNT; ++i) {
		digitalWrite(ledPins[i], i < value ? HIGH : LOW);
	}
}

/****************************************************/
void setup(void)
{
	Serial.begin(115200);
	pinMode(BUTTON_PIN, INPUT);
	for (uint8_t pin : ledPins) {
		pinMode(pin, OUTPUT);
	}
	showCounterOnLeds(0);
}


/****************************************************/
void loop(void)
{
	const int reading = digitalRead(BUTTON_PIN);
	if (reading != previousReading) {
		previousReading = reading;
		lastChangeMs = millis();
	}

	const bool isStable = millis() - lastChangeMs >= DEBOUNCE_MS;
	if (!isStable || reading == debouncedState) {
		return;
	}

	debouncedState = reading;
	if (debouncedState != HIGH) {
		return;
	}

	counter = (counter + 1) % MAX_COUNT_WRAP;
	Serial.print("count=");
	Serial.println(counter);
	showCounterOnLeds(counter);
}
