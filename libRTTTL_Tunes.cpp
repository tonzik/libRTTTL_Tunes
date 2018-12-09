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


#define isdigit(n) (n >= '0' && n <= '9')


libRTTTL_Tunes::libRTTTL_Tunes(int tonePin) {

	_tonePin 	=	tonePin;
}


bool libRTTTL_Tunes::play_RTTTL(char *p) {
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
   if (Serial.available())
    return false;
	}
 return true;
}
