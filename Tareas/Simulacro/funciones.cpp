#include "funciones.h"

// VARIABLES 
volatile bool flagUp = false;
volatile bool flagDown = false;
volatile uint8_t cont = 0;

bool flagMin = true;
bool flagSeg = false;
uint8_t stateLED = LED_MIN_STATE;

unsigned long lastUp = 0;
unsigned long lastDown = 0;

// CONFIGURACIÓN 
void conf(void) {

  Serial.begin(BAUDRATE);

  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);
  pinMode(BTN_MODE, INPUT_PULLUP);
  pinMode(BTN_SAVE, INPUT_PULLUP);
  pinMode(LED_MIN, OUTPUT);
  pinMode(LED_SEG, OUTPUT);

  // Leer EEPROM
  uint8_t minVal = EEPROM.read(CELDA_MIN);
  uint8_t segVal = EEPROM.read(CELDA_SEG);
  stateLED = EEPROM.read(CELDA_LED);

  // Validar rango y corregir EEPROM si es necesario
  if (minVal > MAX) {
    minVal = 0;
    EEPROM.update(CELDA_MIN, minVal);
  }

  if (segVal > MAX) {
    segVal = 0;
    EEPROM.update(CELDA_SEG, segVal);
  }

  if (stateLED > 1) {
    stateLED = LED_MIN_STATE;
    EEPROM.update(CELDA_LED, stateLED);
  }

  // Restaurar modo según último guardado
  if (stateLED == LED_MIN_STATE) {
    cont = minVal;
    flagMin = true;
    flagSeg = false;
    digitalWrite(LED_MIN, HIGH);
    digitalWrite(LED_SEG, LOW);
    Serial.println("=== Sistema Iniciado en MODO MINUTOS ===");
  } 
  else {
    cont = segVal;
    flagSeg = true;
    flagMin = false;
    digitalWrite(LED_SEG, HIGH);
    digitalWrite(LED_MIN, LOW);
    Serial.println("=== Sistema Iniciado en MODO SEGUNDOS ===");
  }

  // Mostrar valores restaurados
  Serial.print("Minutos guardados: ");
  Serial.println(minVal);
  Serial.print("Segundos guardados: ");
  Serial.println(segVal);
  Serial.println("=========================================");
}

// PROCESAR BOTONES 
void processButtons(void) {
  
  unsigned long now = millis();

  if (flagUp == true && (now - lastUp > DEBOUNCE_TIME)) {

    if (cont < MAX) {
      cont++;

      if (flagMin == true) {
        Serial.print("Minuto: ");
      } 
      else {
        Serial.print("Segundo: ");
      }
      Serial.println(cont);
    } 
    else {
      Serial.println("Valor máximo alcanzado");
    }

    lastUp = now;
  }
  flagUp = false;

  if (flagDown == true && (now - lastDown > DEBOUNCE_TIME)) {

    if (cont > MIN) {
      cont--;

      if (flagMin == true) {
        Serial.print("Minuto: ");
      } 
      else {
        Serial.print("Segundo: ");
      }
      Serial.println(cont);
    } 
    else {
      Serial.println("Valor mínimo alcanzado");
    }

    lastDown = now;
  }
  flagDown = false;
}

// ISR 
void subir() {
  flagUp = true;
}

void bajar() {
  flagDown = true;
}

// CAMBIO DE MODO 
void mode(void) {

  static unsigned long lastMode = 0;
  unsigned long now = millis();

  if (digitalRead(BTN_MODE) == LOW && (now - lastMode > DEBOUNCE_TIME)) {

    if (flagMin == true) {
      flagMin = false;
      flagSeg = true;
      stateLED = LED_SEG_STATE;

      digitalWrite(LED_MIN, LOW);
      digitalWrite(LED_SEG, HIGH);
      cont = EEPROM.read(CELDA_SEG);

      if (cont > MAX) {
        cont = 0;
      }

      Serial.println("Modo cambiado → SEGUNDOS");
    } 
    else {
      flagSeg = false;
      flagMin = true;
      stateLED = LED_MIN_STATE;

      digitalWrite(LED_SEG, LOW);
      digitalWrite(LED_MIN, HIGH);
      cont = EEPROM.read(CELDA_MIN);

      if (cont > MAX) {
        cont = 0;
      }

      Serial.println("Modo cambiado → MINUTOS");
    }

    lastMode = now;
  }
}

//  GUARDAR EN EEPROM 
void save(void) {

  static unsigned long lastSave = 0;
  unsigned long now = millis();

  if (digitalRead(BTN_SAVE) == LOW && (now - lastSave > DEBOUNCE_TIME)) {

    if (flagMin == true) {
      EEPROM.update(CELDA_MIN, cont);
      Serial.print("Guardado en EEPROM → MINUTOS = ");
      Serial.println(cont);
    } 
    else {
      EEPROM.update(CELDA_SEG, cont);
      Serial.print("Guardado en EEPROM → SEGUNDOS = ");
      Serial.println(cont);
    }

    EEPROM.update(CELDA_LED, stateLED);
    Serial.println("Estado LED guardado en EEPROM");

    lastSave = now;
  }
}
