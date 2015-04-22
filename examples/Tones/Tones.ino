#include <AccelStepper.h>
#include <Cubetto.h>
#include <sound.h>

//give a name to our Cubetto, in our case "cubetto"
Cubetto cubetto;

void setup() {
  //.init() is required to initialize Cubetto
  cubetto.init();  
  
  delay(1000);
  
  //we write these in the setup to execute them just once
  tone(PRIMO_BUZZER_PIN, PRIMO_NOTE_C6);
  delay(250);
  tone(PRIMO_BUZZER_PIN, PRIMO_NOTE_E6);
  delay(350);
  tone(PRIMO_BUZZER_PIN, PRIMO_NOTE_G6);
  delay(300);
  tone(PRIMO_BUZZER_PIN, PRIMO_NOTE_DS6);
  delay(650);
  tone(PRIMO_BUZZER_PIN, PRIMO_NOTE_F6);
  delay(250);
  tone(PRIMO_BUZZER_PIN, PRIMO_NOTE_B4);
  delay(200);
  noTone(PRIMO_BUZZER_PIN);
}

void loop() {
  //nothing to see here
}