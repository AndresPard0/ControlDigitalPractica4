#include <Arduino.h>
#define SW1 4 
#define SW2 5 
#define SW3 6
#define SW4 7
#define ledVerde 10
#define ledAmarillo 11
#define ledRojo 12 
#define ledAzul 13
int numero = 0;
int contador = 0;
const int leds[4] = {ledVerde, ledAmarillo, ledRojo, ledAzul}; 
const int botones[4] ={4, 5, 6, 7}; 
bool estadoAnterior[4]={true, true, true, true};


void setup (){
  // Configurar Timer1 para generar una interrupción cada 500ms
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT); // Configurar los pines de los LEDs como salidas
    pinMode(botones[i], INPUT_PULLUP); 
  }
  noInterrupts(); // Deshabilitar interrupciones durante la configuración

  // Configurar Timer1
  TCCR1A = 0; // Establecer registros de control en 0 para modo normal
  TCCR1B = 0; // Borra TCCR1B para configuración de nuevo

  // Establecer preescalador en 64 (CS12 = 1)
  TCCR1B |= B00000100;

  // Cargar el valor de comparación en OCR1A
  OCR1A = 12500; // Cuenta hasta 12499 (0 a 12499 = 12500 ciclos), ya que el conteo comienza desde 0

  // Habilitar la interrupción de comparación (TIMER1_COMPA_vect)
  TIMSK1 |= (1 << OCIE1A);

  interrupts(); // Habilitar interrupciones después de la configuración
}

void loop (){
  bool estadoActual[4] = {digitalRead(botones[0]),digitalRead(botones[1]),digitalRead(botones[2]),digitalRead(botones[3])};

  // Verificar si ha ocurrido un flanco de bajada
  if (estadoAnterior[0] == HIGH && estadoActual[0] == LOW) {
    // Se ha detectado un flanco de bajada
    if (numero==1){
      numero = 0;
    }
    else{
      numero = 1;
    }
  }
    if (estadoAnterior[1] == HIGH && estadoActual[1] == LOW) {
    // Se ha detectado un flanco de bajada
    if (OCR1A==12500){
      OCR1A = 7000;
    }
    else{
      OCR1A = 12500;
    }
  }

  // Actualizar el estado anterior del pin
  estadoAnterior[0] = estadoActual[0];estadoAnterior[1] = estadoActual[1];
  delay(50);

}

// Rutina de interrupción para Timer1 cuando se alcanza el valor de comparación
ISR(TIMER1_COMPA_vect) {
  TCNT1 = 0;
  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], LOW);
  }
  
  // Encender el siguiente LED
  digitalWrite(leds[contador], HIGH); 
  
  // Incrementar el contador
  //contador = (contador + 1) % 4;
  contador = (contador +1 + 2*numero ) % 4;
}
