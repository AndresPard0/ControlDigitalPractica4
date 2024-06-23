// botones.h
#ifndef PULSANTES_H
#define PULSANTES_H
typedef enum {
    buttonUp,
    buttonDown,
    buttonFalling,
    buttonRising
} estadosBoton_t;

// Prototipos de funciones
void mefIniciarBoton();
void mefActualizarBoton(int16_t button, int16_t i, bool *botones);
int delayNoBloqueante(int16_t tiempo);
void botonPrecionado(int16_t j, bool *botones);
void botonLiberado();
void BotonesComoEntradaPullUp();
bool LeerBotones (bool *botones);
void SentidoDeSecuencia(bool *botones, int *contador, uint8_t ultimoLed);
void VelocidadDeSecuencia(bool *botones, int *interval);

#endif
