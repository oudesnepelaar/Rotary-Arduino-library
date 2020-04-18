/*
  RotaryEncoder.h - Library for interpreting Data/Clock pin values from a KY040 rotary encoder and translating these into CW or CCW turns.
  Created by Ferrie Bank, 16 January 2020.
  Released into the public domain.
*/

#include "Arduino.h"
#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder(int dataPin, int clockPin, int bufferSize) {
	
	_bufferSize = bufferSize; // take multiple consequentive movements to report 1 full turn (5 matches the notch distance for KY040)
	
	pinMode(dataPin, INPUT);
	pinMode(clockPin, INPUT);
	
	_dataPin = dataPin;
	_clockPin = clockPin;
	
	_dataValue = -1;
	_clockValue = -1;
	_dataPrev = -1;
	_clockPrev = -1;
	
	_bufferLimit = 2 * _bufferSize;
	_bufferLevel = _bufferSize;
	_rotationStatus = 0;
}

int RotaryEncoder::sampleRotationStatus() {
	
	_rotationStatus = 0; // presume static
	
	_dataPrev = _dataValue;
	_clockPrev = _clockValue;

	_dataValue = digitalRead(_dataPin);
	_clockValue = digitalRead(_clockPin);

	if ((_dataValue != _dataPrev) || (_clockValue != _clockPrev)) _determineDirection(); // only true if a change was detected

	return _rotationStatus;
}

void RotaryEncoder::_determineDirection() {

	boolean _isCW;

	if (_dataValue == _clockValue) {

		_isCW = (_dataValue == _dataPrev);

	} else {

		_isCW = (_clockValue == _clockPrev);
	}

	if (_isCW) {

		_bufferLevel++;

	} else {

		_bufferLevel--;
	}

	_interpretBuffer();
}

void RotaryEncoder::_interpretBuffer() {
	
	if (_bufferLevel == 0) { // full complement of CCW movements

		_bufferLevel = _bufferSize;
		_rotationStatus = -1;
		return;
	}

	if (_bufferLevel == _bufferLimit) { // full complement of CW movements

		_bufferLevel = _bufferSize;
		_rotationStatus = 1;
		return;
	}

	_rotationStatus = 0;
}