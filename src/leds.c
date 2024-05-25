#include <Arduino.h>
#include "../inc/hal.h"

//Función para encender un led 
void EncenderLed (int pin){
    digitalWrite(pin, HIGH);
}
//Apagar todos los leds
void ApagarLeds(const int *leds, uint8_t numeroDeLeds){
    for (int i = 0; i < numeroDeLeds; i++){
        digitalWrite(leds[i], LOW);
    }
}

