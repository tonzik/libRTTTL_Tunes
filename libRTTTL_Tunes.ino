#include "libRTTTL_Tunes.h"

// Määritetään buzzerin pinni Arduinoille
// Define buzzer pin
libRTTTL_Tunes player(A0);

// Store data in flash (program) memory
const char s0[] PROGMEM = "JamesBond:d=4,o=5,b=80:32p,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d#6,16d#6,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d6,16c#6,16c#7,c.7,16g#6,16f#6,g#.6";
const char s1[] PROGMEM = "PrinceIgor:d=32,o=6,b=40:16c,16c,4g,f,g,16d#,d,c,d,d#,4f,16g,16f,d#,d,16g5,16g5,4c,d#,f,16d#,d,c,d,c,8a#.5";
const char s2[] PROGMEM = "Halloween:d=4,o=5,b=180:32p,8d6,8g,8g,8d6,8g,8g,8d6,8g,8d#6,8g,8d6,8g,8g,8d6,8g,8g,8d6,8g,8d#6,8g,8c#6,8f#,8f#,8c#6,8f#,8f#,8c#6,8f#,8d6,8f#,8c#6,8f#,8f#,8c#6,8f#,8f#,8c#6,8f#,8d6,8f#";
const char s3[] PROGMEM = "KnightRider:d=4,o=5,b=125:16e,16p,16f,16e,16e,16p,16e,16e,16f,16e,16e,16e,16d#,16e,16e,16e,16e,16p,16f,16e,16e,16p,16f,16e,16f,16e,16e,16e,16d#,16e,16e,16e,16d,16p,16e,16d,16d,16p,16e,16d,16e,16d,16d,16d,16c,16d,16d,16d,16d,16p,16e,16d,16d,16p,16e,16d,16e,16d,16d,16d,16c,16d,16d,16d";
const char s4[] PROGMEM = "TopGun:d=4,o=4,b=31:32p,16c#,16g#,16g#,32f#,32f,32f#,32f,16d#,16d#,32c#,32d#,16f,32d#,32f,16f#,32f,32c#,16f,d#,16c#,16g#,16g#,32f#,32f,32f#,32f,16d#,16d#,32c#,32d#,16f,32d#,32f,16f#,32f,32c#,g#";
const char s5[] PROGMEM = "Dallas:d=4,o=6,b=50:32p,32b.5,8c,32g.5,8g,32c.,16e.,32d.,32e.,16c.,16g.5,16c.,16a.,16g.,32e.,32f.,g,16g.5,16c.,16a.,16g.,32e.,32f.,16g.,32d.,32e.,16c.,16g.5,16c.,32e.,32f.,8d,32g.,g";
const char s6[] PROGMEM = "MenBehaving:d=8,o=5,b=125:32p,16f,g#,4c6,a#,16g#,a#.,g#,16g,g#.,g,f.,16f,g#,4c6,a#,16g#,a#.,g#,16f,d#.6,c#6,c.6,16f,g#,4c6,a#,16g#,a#.,g#,16g,g#.,g,16f";

char buffer[512];    // make sure this is large enough for the largest string it must hold


void setup() {

}

void loop() {

  // Soittaa kappaleen 10 sekunnin välein
  // Repeat the song every 10 seconds
  strcpy_P(buffer, (char*)s6);    // Copy song from progmem to buffer
  player.play_RTTTL(buffer);
  delay(10000);
}
