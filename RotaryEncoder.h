/*
  RotaryEncoder.h - Library for interpreting Data/Clock pin values from a KY040 rotary encoder and translating these into CW or CCW turns.
  Created by Ferrie Bank, 16 January 2020.
  Released into the public domain.
*/

#ifndef RotaryEncoder_h
#define RotaryEncoder_h

#include "Arduino.h"

class RotaryEncoder {
	
	public:
		RotaryEncoder(int dataPin, int clockPin, int bufferSize); // (larger buffers require more movement before it is reported as a turn)
		int sampleRotationStatus(void); // returns -1 for a CCW turn, 1 for a CW turn, 0 for no turn detected
		
	private:
		int _dataPin;
		int _clockPin;
		int _bufferSize;
		int _bufferLimit;
		
		int _dataValue;
		int _clockValue;
		int _dataPrev;
		int _clockPrev;
		
		int _bufferLevel;
		int _rotationStatus;
		
		void _determineDirection(void);
		void _interpretBuffer(void);
};

#endif