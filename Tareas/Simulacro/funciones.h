#ifndef FUNCIONES_H  
#define FUNCIONES_H

#include <Arduino.h> 
#include <stdint.h> 
#include <EEPROM.h>

// CONFIGURACIÓN
#define BAUDRATE 9600

// Pines
#define BTN_UP     2   // interrupción
#define BTN_DOWN   3   // interrupción
#define BTN_SAVE   4   // polling
#define BTN_MODE   5   // polling
#define LED_MIN   6
#define LED_SEG   7

// Límites
#define MAX 60
#define MIN 0

// EEPROM
#define CELDA_SEG  0
#define CELDA_MIN  1
#define CELDA_LED  2

// Estado de LED
#define LED_MIN_STATE  1
#define LED_SEG_STATE  0

// Tiempo de debounce
#define DEBOUNCE_TIME 200  // ms

// VARIABLES GLOBALES 
extern volatile bool flagUp;
extern volatile bool flagDown;
extern volatile uint8_t cont;  
extern bool flagMin;
extern bool flagSeg;
extern uint8_t stateLED;

// FUNCIONES
void conf(void);
void mode(void);
void save(void);
void processButtons(void);
void subir(void);
void bajar(void);

#endif
