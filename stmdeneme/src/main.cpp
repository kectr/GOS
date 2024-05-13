#include <Arduino.h>

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    digitalWrite(1,LED_BUILTIN);
    delay(100);
    digitalWrite(0,LED_BUILTIN);
    delay(100);
}
