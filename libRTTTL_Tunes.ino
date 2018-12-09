/* (c)2018 CrashSoft
 * Commands:
 * 0 - 9  -- Number of song to play
 * A      -- Autoplay on/off
 * D      -- Set delay for autoplay (1-60 secs)
 */
#include "libRTTTL_Tunes.h"

#define       SERIAL_INPUT_SIZE     32        // Calculate based on max input size expected for one command
#define       countof(a) (sizeof(a) / sizeof(a[0]))

// Store data in flash (program) memory
const char s0[] PROGMEM = "JamesBond:d=4,o=5,b=80:32p,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d#6,16d#6,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d6,16c#6,16c#7,c.7,16g#6,16f#6,g#.6";
const char s1[] PROGMEM = "PrinceIgor:d=32,o=6,b=40:16c,16c,4g,f,g,16d#,d,c,d,d#,4f,16g,16f,d#,d,16g5,16g5,4c,d#,f,16d#,d,c,d,c,8a#.5";
const char s2[] PROGMEM = "Halloween:d=4,o=5,b=180:32p,8d6,8g,8g,8d6,8g,8g,8d6,8g,8d#6,8g,8d6,8g,8g,8d6,8g,8g,8d6,8g,8d#6,8g,8c#6,8f#,8f#,8c#6,8f#,8f#,8c#6,8f#,8d6,8f#,8c#6,8f#,8f#,8c#6,8f#,8f#,8c#6,8f#,8d6,8f#";
const char s3[] PROGMEM = "KnightRider:d=4,o=5,b=125:16e,16p,16f,16e,16e,16p,16e,16e,16f,16e,16e,16e,16d#,16e,16e,16e,16e,16p,16f,16e,16e,16p,16f,16e,16f,16e,16e,16e,16d#,16e,16e,16e,16d,16p,16e,16d,16d,16p,16e,16d,16e,16d,16d,16d,16c,16d,16d,16d,16d,16p,16e,16d,16d,16p,16e,16d,16e,16d,16d,16d,16c,16d,16d,16d";
const char s4[] PROGMEM = "TopGun:d=4,o=4,b=31:32p,16c#,16g#,16g#,32f#,32f,32f#,32f,16d#,16d#,32c#,32d#,16f,32d#,32f,16f#,32f,32c#,16f,d#,16c#,16g#,16g#,32f#,32f,32f#,32f,16d#,16d#,32c#,32d#,16f,32d#,32f,16f#,32f,32c#,g#";
const char s5[] PROGMEM = "Dallas:d=4,o=6,b=50:32p,32b.5,8c,32g.5,8g,32c.,16e.,32d.,32e.,16c.,16g.5,16c.,16a.,16g.,32e.,32f.,g,16g.5,16c.,16a.,16g.,32e.,32f.,16g.,32d.,32e.,16c.,16g.5,16c.,32e.,32f.,8d,32g.,g";
const char s6[] PROGMEM = "MenBehaving:d=8,o=5,b=125:32p,16f,g#,4c6,a#,16g#,a#.,g#,16g,g#.,g,f.,16f,g#,4c6,a#,16g#,a#.,g#,16f,d#.6,c#6,c.6,16f,g#,4c6,a#,16g#,a#.,g#,16g,g#.,g,16f";

// Set up a table to refer to your songs.
const char    *const string_table[] PROGMEM = { s0, s1, s2, s3, s4, s5, s6 };
char          buffer[512];    // make sure this is large enough for the largest string it must hold
char          songName[16];

const char    *OnOFF[] = {"Off", "On"};

char          Serial_buffer[SERIAL_INPUT_SIZE + 1];
int           Serial_pos = 0;
int           auto_play = true;

// Määritetään buzzerin pinni Arduinoille
// Define buzzer pin
libRTTTL_Tunes player(A2);
int           cur_song=0;
int           num_songs = countof(string_table);
int           song_delay = 10000;
unsigned int  delayTimer=0;

void setup() {
  Serial.begin(115200);
  Serial.print(F("Number of songs: "));
  Serial.println(num_songs);
  //delayTimer = millis();
}

void loop() {
  
  if (auto_play && millis() > delayTimer + song_delay) {
    playSong(cur_song);
    
    delayTimer = millis();
    cur_song++;
    if (cur_song > num_songs)
      cur_song = 0;
  }

  //*** Got a command from serial
  if (serial_Event()) {
    char cmd = toupper(Serial_buffer[0]);
        
    if (cmd >= '0' && cmd <= '9' ) { 
        sscanf (Serial_buffer,"%d", &cur_song); 
        if (cur_song < 0 || cur_song >= num_songs) 
          cur_song = 0;
          playSong(cur_song);
    }
            
    if (cmd == 'A')
    {
      auto_play = !auto_play;
      Serial.print(F("Autoplay "));
      Serial.println(OnOFF[auto_play]);
    }      
    
    if (cmd == 'D')
    {
      int Delay=0;      
      sscanf (Serial_buffer,"%*c%i", &Delay);
                   
      if (Delay > 0 && Delay < 60) {      
        song_delay = Delay * 1000; 
        Serial.print(F("New delay (in sec)"));
        Serial.println(Delay);
      }
    }
    
  }

  delay(100);
}

void playSong(int songNum){
  strcpy_P(buffer, (char*)pgm_read_word(&(string_table[songNum])));    // Copy song from progmem to buffer

  // Read song name
  for (int i=0; i<countof(songName); i++) {
    songName[i] = (buffer[i] != ':') ? buffer[i] : 0;
  }
    
  Serial.print(F("Playing song "));
  Serial.print(songNum);
  Serial.print(" - ");
  Serial.println(songName);
  
  // Start playing
  if (!player.play_RTTTL(buffer))    
      Serial.println(F("Play was interrupted"));
  
}


bool serial_Event() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    Serial_buffer[Serial_pos] = inChar;

    Serial_pos++;
    // if reached max buf size or the incoming character is a newline return string terminated with zero
    if (inChar == '\n' || Serial_pos == SERIAL_INPUT_SIZE - 1) {
      Serial_buffer[Serial_pos + 1] = 0;
      Serial_pos = 0;
      return true;
    }
  }
  return false;
}
