#include <Arduino.h>
#include "../inc/hal.h"

void EncenderLed (int pin){
    digitalWrite(pin, HIGH);
}

void ApagarLeds(const int *leds, uint8_t numeroDeLeds){
    for (int i = 0; i < numeroDeLeds; i++){
        digitalWrite(leds[i], LOW);
    }
}

