#ifndef FUNCIONES_H  //protege al archivo para que no lo llamen una y otra vez
#define FUNCIONES_H

#include <Arduino.h> //incluye la libreria de arduino
#include <stdint.h> //usar variables enteras de distinto tama;o 
#include <EEPROM.h>

#define BAUDRATE 9600
#define BTN1 2 //2 y 3 pines para interrupciones 
#define BTN2 3
#define BTNC1 4
#define BTNC2 5
#define LED 13
#define TM  2000
#define CELDA 0
#define MAXVOL 100
#define MINVOL 0
#define DEFVOL 50
#define MAXCANAL 9
#define MINCANAL 1




void conf(void);
void blink(void);
void cambiarCanal(void);



#endif

//millis, podemos ocupar todos los pines, no contamos con muchos temporizadores, retardante no bloqueante, desactivar falsos positivos 
//interrupciones, maximo de dos pines pueden ser activadas en cualquier punto
//delay, retardante bloqueante de toda la placa, los delay se suman
