#include "funciones.h"

volatile uint8_t cont =  EEPROM.read(CELDA); // no supervisa constantemente el valor, no pasa nada si hay cambios, quita la parte negativa (+255)

void setup() {
  if(cont > 100){
    EEPROM.write(CELDA,DEFVOL); //Sin llaves solo si es una instruccion
  }
  conf();
  attachInterrupt(digitalPinToInterrupt(BTN1),subirVol,RISING);
  attachInterrupt(digitalPinToInterrupt(BTN2),bajarVol,RISING);


}

void loop() {
  blink();
  cambiarCanal();

}


//ISRs
void subirVol(){
  if(cont < MAXVOL){
    cont ++;
    EEPROM.write(CELDA,cont); //EEPROM.update, no deja escribir el mismo numero sobre la celda
  }

}

void bajarVol(){
  if(cont > MINVOL){
    cont --;
    EEPROM.write(CELDA,cont);
  }

}

