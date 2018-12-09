#include "libRTTTL_Tunes.h"

// Määritetään buzzerin pinni Arduinoille
// Define buzzer pin
libRTTTL_Tunes player(A0);

void setup() {

}

void loop() {

  // Soittaa kappaleen 10 sekunnin välein
  // Repeat the song every 10 seconds
  player.playTuneNumber(1);
  delay(10000);
}
