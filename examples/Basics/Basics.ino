#include <AccelStepper.h>
#include <Cubetto.h>
#include <sound.h>

//give a name to our Cubetto, in our case "cubetto"
Cubetto cubetto;

void setup() {
  //we write these in the setup to execute them just once
  cubetto.forward();
  cubetto.left();  
  cubetto.right();    
  cubetto.playHappyTune();
}

void loop() {
  //nothing to see here
}