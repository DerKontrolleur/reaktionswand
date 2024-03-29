/*	This class can be used to read values
	of up to 8 sensors connected via shift
	register.	*/

#ifndef SENSOR_H
#define SENSOR_H

#include "Arduino.h"

class Sensor {
	private:
		int _datapin;
		int _latchpin;
		int _clockpin;

		byte _sensor;

	public:
  		Sensor(int latchpin, int datapin, int clockpin);

		void set(int latchpin, int datapin, int clockpin);
		int check(int i);
		byte get();
		void printStatus(byte value);
		void print();
		byte ShiftIn(int datapin, int clockpin);
};

#endif

