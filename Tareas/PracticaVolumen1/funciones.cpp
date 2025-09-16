#include "funciones.h"
uint8_t vol = EEPROM.read(CELDA);

void conf(void){
  Serial.begin(BAUDRATE);
  pinMode(BTNUP, INPUT_PULLUP);
  pinMode(BTNDOWN, INPUT_PULLUP);
  if (vol>MAXVOL){
    vol=MEDIA;
    EEPROM.write(CELDA,vol);
  }
    
}

void subir(void){
  if (vol<MAXVOL)
    vol++;
  Serial.println(vol);
  EEPROM.update(CELDA,vol);
}

void bajar(void){
  if (vol>MINVOL)
    vol--;
  Serial.println(vol);
  EEPROM.update(CELDA,vol);
  
}