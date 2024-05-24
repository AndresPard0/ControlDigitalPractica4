#include <Arduino.h>
extern "C" {
  #include "inc/pulsantes.h"
  #include "inc/leds.h"
  #include "inc/hal.h"
}

void setup () {
  //Encender los leds
  Serial.begin(9600);
  LedsComoSalidas();
  BotonesComoEntradaPullUp();
}

void loop (){
  static bool a = false;
  a = digitalRead(boton1);
  if (a == false){
    Serial.println(a);
  }
  
  delay(300);
}