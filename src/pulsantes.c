#include <Arduino.h>
#include <stdbool.h>
#include "../inc/hal.h"
#include "../inc/pulsantes.h"
static bool botonesAnteriores[4] = {true, true, true, true};  
unsigned long tiempoInicial = 0;
estadosBoton_t estadosBoton[4];
void BotonesComoEntradaPullUp(){
    pinMode(boton1, INPUT_PULLUP);
    pinMode(boton2, INPUT_PULLUP);
    pinMode(boton3, INPUT_PULLUP);
    pinMode(boton4, INPUT_PULLUP);
 };

bool LeerBotones (bool *botones){
    const int pulsante [4] = {boton1, boton2, boton3, boton4};
    for (int i = 0; i < 4; i++) {
        mefActualizarBoton(pulsante[i],i,botones);
    //     bool estadoActual = digitalRead(pulsante[i]);
    //     // Verificar si el estado actual es diferente al estado anterior
    //     if (estadoActual==LOW && botonesAnteriores[i]==HIGH) {
    //         //Para evitar problemas con doble boton precionado se toma en cuenta
    //         //si uno de los botones presionado ya se encontraba en true


    //     //Actualizar el estado anterior del botón
    //     botonesAnteriores[i] = estadoActual;
        }

}

//Segun el boton precionado se utiliza una forma de contar diferente
void SentidoDeSecuencia(bool *botones, int *contador, uint8_t ultimoLed){
    //Conteo descendente
    if (botones[0]){
        *contador = (*contador - 1 + ultimoLed) % ultimoLed; 
    }//Conteo ascendente
    else{
        *contador = (*contador + 1) % ultimoLed; 
    }
}

//Se cambia el intervalo para el cual funciona la secuencia
void VelocidadDeSecuencia(bool *botones, int *interval){
    if (botones[2]){
        *interval = 200;
    }else{
        *interval = 750;
    }
}


void mefIniciarBoton() {
    estadosBoton[0] = buttonUp;
    estadosBoton[1] = buttonUp;
    estadosBoton[2] = buttonUp;
    estadosBoton[3] = buttonUp;
}

void botonPrecionado(int16_t j, bool *botones) {
    digitalWrite(13, HIGH);
            if (j==0 && botones[j] != true){
                botones[j] = !botones[j];
                botones[j+1] = !botones[j+1];
            }
            if (j==1 && botones[j] != true){
                botones[j-1] = !botones[j-1];
                botones[j] = !botones[j];
            }
            if (j==2 && botones[j] != true){
                botones[j] = !botones[j];
                botones[j+1] = !botones[j+1];
            }
            if (j==3 && botones[j] != true){
                botones[j-1] = !botones[j-1];
                botones[j] = !botones[j];
            }            
}

void botonLiberado() {
    digitalWrite(13, LOW);
}

int delayNoBloqueante(int16_t tiempo) {
    // Obtener el tiempo actual
    unsigned long tiempoActual = millis();
    // Verificar si el tiempo transcurrido es mayor o igual al tiempo especificado
    if (tiempoActual - tiempoInicial >= tiempo) {
        tiempoInicial = tiempoActual;
        return 1;  // Han pasado al menos 'tiempo' milisegundos
    } else {
        return 0; // Aún no han pasado 'tiempo' milisegundos
    }
}

void mefActualizarBoton(int16_t button, int16_t i, bool *botones) {
    switch (estadosBoton[i]) {
    case buttonUp:
        if (!digitalRead(button)) {
            estadosBoton[i] = buttonFalling;
        }
        break;

    case buttonDown:
        if (digitalRead(button)) {
            estadosBoton[i] = buttonRising;
        }
        break;

    case buttonFalling:
        if (delayNoBloqueante(40)) {
            if (!digitalRead(button)) {
                estadosBoton[i] = buttonDown;
                botonPrecionado(i,botones);
            } else {
                estadosBoton[i] = buttonUp;
            }
        }
        break;

    case buttonRising:
        if (delayNoBloqueante(40)) {
            if (digitalRead(button)) {
                estadosBoton[i] = buttonUp;
                botonLiberado();
            } else {
                estadosBoton[i] = buttonDown;
            }
        }
        break;

    default:
        mefIniciarBoton();
        break;
    }
}