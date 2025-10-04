#include "funciones.h"

unsigned long lastCanalTime = 0;
const unsigned long debounceCanal = 300; // tiempo antirrebote

void conf(void){
  Serial.begin(BAUDRATE);
  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  pinMode(BTNC1, INPUT_PULLUP);
  pinMode(BTNC2, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
}

void blink(void){
  digitalWrite(LED, HIGH);
  delay(TM);
  digitalWrite(LED, LOW);
  delay(TM);
}

void cambiarCanal(void){
  unsigned long now = millis();
  if(now - lastCanalTime >= debounceCanal){
    
    if(!digitalRead(BTNC1)){  // subir canal
      uint8_t canal = EEPROM.read(CELDA);
      if(canal < MAXCANAL){
        canal++;
        EEPROM.write(CELDA, canal);
        Serial.print("Canal subido a: ");
        Serial.println(canal);
      }
    }

    if(!digitalRead(BTNC2)){  // bajar canal
      uint8_t canal = EEPROM.read(CELDA);
      if(canal > MINCANAL){
        canal--;
        EEPROM.write(CELDA, canal);
        Serial.print("Canal bajado a: ");
        Serial.println(canal);
      }
    }

    lastCanalTime = now;
  }
}









