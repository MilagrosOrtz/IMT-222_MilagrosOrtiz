#define NUM_LEDS 15
#define DELAY 500

#define PRIMER_LED 2

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < NUM_LEDS ; i++){
    pinMode(PRIMER_LED + i, OUTPUT);
  }

}

void loop() {
  for (int i=0; i< NUM_LEDS;i++){
    digitalWrite(PRIMER_LED + i, HIGH);
    delay(DELAY);
  }

}
