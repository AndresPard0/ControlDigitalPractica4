#include <Arduino.h>
#include "../inc/hal.h"

BotonesComoEntradaPullUp(){
    pinMode(boton1, INPUT_PULLUP);
    pinMode(boton2, INPUT_PULLUP);
    pinMode(boton3, INPUT_PULLUP);
    pinMode(boton4, INPUT_PULLUP);
 };

