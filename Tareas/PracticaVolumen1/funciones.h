#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <Arduino.h>
#include <EEPROM.h>

#define   BTNUP   2
#define   BTNDOWN 3
#define   BAUDRATE  9600
#define   MINVOL  0
#define   MAXVOL  10
#define   CELDA   0
#define   MEDIA   5

extern uint8_t vol;

void conf(void);
void subir();
void bajar();
#endif