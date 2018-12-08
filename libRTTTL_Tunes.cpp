/*
 * 
 *  Kirjasto libRTTTL_Tunes on luotu seuraavien tietojen ja koodien perusteella:
 *  The libRTTTL_Tunes library was made based on the following data and code:
 *  
 *        https://www.instructables.com/id/RTTL-Tunes-on-arduino/
 * 
 *        // A fun sketch to demonstrate the use of the tone() function written by Brett Hagman.
 * 
 *        // This plays RTTTL (RingTone Text Transfer Language) songs using the
 *        // now built-in tone() command in Wiring and Arduino.
 *        // Written by Brett Hagman
 *        // http://www.roguerobotics.com/
 * 
 *        // To play the output on a small speaker (i.e. 8 Ohms or higher), simply use
 *        // a 1K Ohm resistor from the output pin to the speaker, and connect the other
 *        // side of the speaker to ground.
 * 
 */

#include <Arduino.h>
#include "libRTTTL_Tunes.h"

#define OCTAVE_OFFSET 0

// These values can also be found as constants in the Tone library (Tone.h)
int notes[] = { 0,
262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494,
523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988,
1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976,
2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951
};

char *song1 = "PrinceIgor:d=32,o=6,b=40:16c,16c,4g,f,g,16d#,d,c,d,d#,4f,16g,16f,d#,d,16g5,16g5,4c,d#,f,16d#,d,c,d,c,8a#.5";
char *song2 = "Halloween:d=4,o=5,b=180:32p,8d6,8g,8g,8d6,8g,8g,8d6,8g,8d#6,8g,8d6,8g,8g,8d6,8g,8g,8d6,8g,8d#6,8g,8c#6,8f#,8f#,8c#6,8f#,8f#,8c#6,8f#,8d6,8f#,8c#6,8f#,8f#,8c#6,8f#,8f#,8c#6,8f#,8d6,8f#";
char *song3 = "JamesBond:d=4,o=5,b=80:32p,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d#6,16d#6,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d6,16c#6,16c#7,c.7,16g#6,16f#6,g#.6";
char *song4 = "KnightRider:d=4,o=5,b=125:16e,16p,16f,16e,16e,16p,16e,16e,16f,16e,16e,16e,16d#,16e,16e,16e,16e,16p,16f,16e,16e,16p,16f,16e,16f,16e,16e,16e,16d#,16e,16e,16e,16d,16p,16e,16d,16d,16p,16e,16d,16e,16d,16d,16d,16c,16d,16d,16d,16d,16p,16e,16d,16d,16p,16e,16d,16e,16d,16d,16d,16c,16d,16d,16d";
char *song5 = "TopGun:d=4,o=4,b=31:32p,16c#,16g#,16g#,32f#,32f,32f#,32f,16d#,16d#,32c#,32d#,16f,32d#,32f,16f#,32f,32c#,16f,d#,16c#,16g#,16g#,32f#,32f,32f#,32f,16d#,16d#,32c#,32d#,16f,32d#,32f,16f#,32f,32c#,g#";
char *song6 = "Dallas:d=4,o=6,b=50:32p,32b.5,8c,32g.5,8g,32c.,16e.,32d.,32e.,16c.,16g.5,16c.,16a.,16g.,32e.,32f.,g,16g.5,16c.,16a.,16g.,32e.,32f.,16g.,32d.,32e.,16c.,16g.5,16c.,32e.,32f.,8d,32g.,g";
char *song7 = "MenBehaving:d=8,o=5,b=125:32p,16f,g#,4c6,a#,16g#,a#.,g#,16g,g#.,g,f.,16f,g#,4c6,a#,16g#,a#.,g#,16f,d#.6,c#6,c.6,16f,g#,4c6,a#,16g#,a#.,g#,16g,g#.,g,16f";

#define isdigit(n) (n >= '0' && n <= '9')


libRTTTL_Tunes::libRTTTL_Tunes(int tonePin) {

	_tonePin 	=	tonePin;
}

void libRTTTL_Tunes::playTuneNumber(int number) {

	if (number == 1) {
		play_RTTTL(song1);
	}

	if (number == 2) {
		play_RTTTL(song2);
	}

	if (number == 3) {
		play_RTTTL(song3);
	}

	if (number == 4) {
		play_RTTTL(song4);
	}

	if (number == 5) {
		play_RTTTL(song5);
	}

	if (number == 6) {
		play_RTTTL(song6);
	}

	if (number == 7) {
		play_RTTTL(song7);
	}

}

void libRTTTL_Tunes::play_RTTTL(char *p) {
	// Absolutely no error checking in here

	byte default_dur = 4;
	byte default_oct = 6;
	int bpm = 63;
	int num;
	long wholenote;
	long duration;
	byte note;
	byte scale;

	// format: d=N,o=N,b=NNN:
	// find the start (skip name, etc)

	while(*p != ':') p++;    // ignore name
	p++;                     // skip ':'

	// get default duration
	if(*p == 'd')
	{
		p++; p++;              // skip "d="
		num = 0;
		while(isdigit(*p))
		{
			num = (num * 10) + (*p++ - '0');
 		}
		if(num > 0) default_dur = num;
		p++;                   // skip comma
	}

	// Serial.print("ddur: "); Serial.println(default_dur, 10);

	// get default octave
	if(*p == 'o')
		{
		p++; p++;              // skip "o="
		num = *p++ - '0';
		if(num >= 3 && num <=7) default_oct = num;
		p++;                   // skip comma
	}

	// Serial.print("doct: "); Serial.println(default_oct, 10);

	// get BPM
	if(*p == 'b')
	{
		p++; p++;              // skip "b="
		num = 0;
		while(isdigit(*p))
		{
			num = (num * 10) + (*p++ - '0');
		}
		bpm = num;
		p++;                   // skip colon
	}

	// Serial.print("bpm: "); Serial.println(bpm, 10);

	// BPM usually expresses the number of quarter notes per minute
	wholenote = (60 * 1000L / bpm) * 4;  // this is the time for whole note (in milliseconds)

	// Serial.print("wn: "); Serial.println(wholenote, 10);


	// now begin note loop
	while(*p)
	{
		// first, get note duration, if available
		num = 0;
		while(isdigit(*p))
		{
			num = (num * 10) + (*p++ - '0');
		}
    
		if(num) duration = wholenote / num;
		else duration = wholenote / default_dur;  // we will need to check if we are a dotted note after

		// now get the note
		note = 0;

		switch(*p)
		{
			case 'c':
				note = 1;
				break;
			case 'd':
				note = 3;
				break;
			case 'e':
				note = 5;
				break;
			case 'f':
				note = 6;
				break;
			case 'g':
				note = 8;
				break;
			case 'a':
				note = 10;
				break;
			case 'b':
				note = 12;
				break;
			case 'p':
			default:
				note = 0;
		}
		p++;

		// now, get optional '#' sharp
		if(*p == '#')
		{
			note++;
			p++;
		}

		// now, get optional '.' dotted note
		if(*p == '.')
		{
			duration += duration/2;
			p++;
		}
  
		// now, get scale
		if(isdigit(*p))
		{
			scale = *p - '0';
			p++;
		}
		else
		{
			scale = default_oct;
		}

		scale += OCTAVE_OFFSET;

		if(*p == ',')
			p++;       // skip comma for next note (or we may be at the end)

		// now play the note

		if(note)
		{
			/*
			Serial.print("Playing: ");
			Serial.print(scale, 10); Serial.print(' ');
			Serial.print(note, 10); Serial.print(" (");
			Serial.print(notes[(scale - 4) * 12 + note], 10);
			Serial.print(") ");
			Serial.println(duration, 10);
			*/
			tone(_tonePin, notes[(scale - 4) * 12 + note]);
			delay(duration);
			noTone(_tonePin);
		}
		else
		{
			/*
			Serial.print("Pausing: ");
			Serial.println(duration, 10);
			*/
			delay(duration);
		}
	}
}