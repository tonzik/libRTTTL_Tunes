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

#ifndef libRTTTL_Tunes_h
#define libRTTTL_Tunes_h

#include <Arduino.h>

class libRTTTL_Tunes {

	public:
  
    	libRTTTL_Tunes(int);

    	void playTuneNumber(int);
    	bool play_RTTTL(char *p);

	private:

		int _tonePin;
};

#endif
