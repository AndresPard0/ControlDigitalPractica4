#include <Arduino.h>
extern "C" {
  #include "inc/pulsantes.h"
  #include "inc/leds.h"
  #include "inc/hal.h"
}
typedef int gpioMap_t; // Ejemplo de definición de gpioMap_t como un alias para int

const gpioMap_t led1 = 10; // Asignación de valores a las constantes LED
const gpioMap_t led2 = 11;
const gpioMap_t led3 = 12;
const gpioMap_t led4 = 13;

const gpioMap_t secuencia[] = {led1, led2, led3, led4};
const uint8_t ultimoLed = sizeof(secuencia)/sizeof(gpioMap_t);
bool botones[4] = {false, true, true, false};

void setup () {
  //Encender los leds
  Serial.begin(115200);
  for (int i = 0; i<ultimoLed; i++){
    pinMode(secuencia[i], OUTPUT);
  }
  //Programar botones como entradas pullup
  BotonesComoEntradaPullUp();
}

void loop (){
  //Variable para iterar la secuencia
  static int contador = -1; 
  //Variable para determinar el tiempo de encendido de la sucuencia
  static int interval = 750;
  //Tiempos para determinar cuando apagar y prender los leds
  static unsigned long previusMillis = 0;
  static unsigned long tiempoBoton = 0;
  unsigned long currentMillis = millis();  
  
  LeerBotones(botones);
  Serial.print(botones[0]);
  Serial.print(botones[1]);
  Serial.print(botones[2]);
  Serial.print(botones[3]);
  Serial.println();

   if (currentMillis - previusMillis >= interval) {
    //Apagar los leds
    ApagarLeds(secuencia, ultimoLed);
    //Contador para controlar el sentido de la secuencia
    SentidoDeSecuencia(botones, &contador, ultimoLed);
    VelocidadDeSecuencia(botones, &interval);
    EncenderLed(secuencia[contador]);
    // Guarda el tiempo actual como referencia para el próximo cambio de estado
    previusMillis = currentMillis;
  }

}