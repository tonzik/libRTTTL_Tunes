#include <libRTTTL_Tunes.h>

// Määritetään buzzerin pinni Arduinoille
libRTTTL_Tunes player(A0);

void setup() {

}

void loop() {

  // Soitetaan kappaleet 1-7 vuorotellen, 10 sekunnin välein
  // Voidaan myös käyttää toistamaan tietty kappale kommennolla esim. player.playTuneNumber(1)
  for(int i = 1; i < 8; i++) {
    player.playTuneNumber(i);
    delay(10000);
  }
}
