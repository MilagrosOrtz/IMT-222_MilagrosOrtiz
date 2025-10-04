#include "funciones.h"

void setup() {

  conf();

  attachInterrupt(digitalPinToInterrupt(BTN_UP), subir, RISING);
  attachInterrupt(digitalPinToInterrupt(BTN_DOWN), bajar, RISING);
}

void loop() {

  processButtons();  // manejo de interrupciones con millis
  mode();            // cambiar entre minutos y segundos
  save();            // guardar valores en EEPROM
}
