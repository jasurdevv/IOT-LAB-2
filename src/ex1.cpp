#include "Arduino.h"

struct ChaseStep
{
    uint8_t pin;
    const char *name;
};

const ChaseStep chaseSteps[] = {
    {26, "RED"},
    {27, "GREEN"},
    {12, "YELLOW"},
    {14, "BLUE"},
    {12, "YELLOW"},
    {27, "GREEN"},
};
const uint8_t CHASE_STEP_COUNT = sizeof(chaseSteps) / sizeof(chaseSteps[0]);
const unsigned long CHASE_DELAY_MS = 150;
uint8_t currentStep = 0;

static void turnAllLedsOff(void)
{
    for (const ChaseStep &step : chaseSteps)
    {
        digitalWrite(step.pin, LOW);
    }
}

/****************************************************/
void setup(void)
{
    Serial.begin(115200);
    for (const ChaseStep &step : chaseSteps)
    {
        pinMode(step.pin, OUTPUT);
    }
    turnAllLedsOff();
}

/****************************************************/
void loop(void)
{
    const ChaseStep &step = chaseSteps[currentStep];

    turnAllLedsOff();
    digitalWrite(step.pin, HIGH);
    Serial.print("chase=");
    Serial.println(step.name);
    delay(CHASE_DELAY_MS);

    currentStep = (currentStep + 1) % CHASE_STEP_COUNT;
}
