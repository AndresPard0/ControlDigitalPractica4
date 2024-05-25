#include <Arduino.h>
#include <stdbool.h>
#include "../inc/hal.h"

void BotonesComoEntradaPullUp(){
    pinMode(boton1, INPUT_PULLUP);
    pinMode(boton2, INPUT_PULLUP);
    pinMode(boton3, INPUT_PULLUP);
    pinMode(boton4, INPUT_PULLUP);
 };

bool LeerBotones (bool *botones){
    static bool botonesAnteriores[4] = {true, true, true, true};  
    const int pulsante [4] = {boton1, boton2, boton3, boton4};
    for (int i = 0; i < 4; i++) {
        bool estadoActual = digitalRead(pulsante[i]);

        // Verificar si el estado actual es diferente al estado anterior
        if (estadoActual==LOW && botonesAnteriores[i]==HIGH) {
            if (i==0 && botones[i] != true){
                botones[i] = !botones[i];
                botones[i+1] = !botones[i+1];
            }
            if (i==1 && botones[i] != true){
                botones[i-1] = !botones[i-1];
                botones[i] = !botones[i];
            }
            if (i==2 && botones[i] != true){
                botones[i] = !botones[i];
                botones[i+1] = !botones[i+1];
            }
            if (i==3 && botones[i] != true){
                botones[i-1] = !botones[i-1];
                botones[i] = !botones[i];
            }            

        }

        // Actualizar el estado anterior del botón
        botonesAnteriores[i] = estadoActual;
    }

}

void SentidoDeSecuencia(bool *botones, int *contador, uint8_t ultimoLed){
    if (botones[0]){
        *contador = (*contador - 1 + ultimoLed) % ultimoLed; 
    }else{
        *contador = (*contador + 1) % ultimoLed; 
    }
}

void VelocidadDeSecuencia(bool *botones, int *interval){
    if (botones[2]){
        *interval = 200;
    }else{
        *interval = 750;
    }
}


