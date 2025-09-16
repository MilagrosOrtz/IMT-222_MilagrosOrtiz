#include "funciones.h"

unsigned long tiempoReboteSubir = 0;
unsigned long tiempoReboteBajar = 0;
const unsigned long tiempoAntire = 500; 

void setup() {
  conf();
}

void loop() {
  Serial.println(vol);

  if (!digitalRead(BTNUP) && (millis() - tiempoReboteSubir > tiempoAntire)) {
    subir();
    tiempoReboteSubir = millis(); 
  }

  if (!digitalRead(BTNDOWN) && (millis() - tiempoReboteBajar > tiempoAntire)) {
    bajar();
    tiempoReboteBajar = millis();
  }
}
