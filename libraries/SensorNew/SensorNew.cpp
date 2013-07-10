#include "SensorNew.h"

Sensor::Sensor(int latchpin, int datapin, int clockpin) {
	_latchpin = latchpin;
	_datapin = datapin;
	_clockpin = clockpin;

	pinMode(_latchpin, OUTPUT);
	pinMode(_clockpin, OUTPUT); 
	pinMode(_datapin, INPUT);

	digitalWrite(_latchpin, LOW);
	delayMicroseconds(5);
	digitalWrite(_latchpin, HIGH);

	_sensor = ShiftIn(_datapin, _clockpin);
}

byte Sensor::get() {
	return _sensor;
}

byte Sensor::ShiftIn(int datapin, int clockpin) {
	int i;
  	int temp = 0;
  	int pinstate;
  	byte datain = 0;

  	pinMode(clockpin, OUTPUT);
  	pinMode(datapin, INPUT);

  	for(i = 7; i >= 0; i--) {

   		digitalWrite(clockpin, 0);
    		delayMicroseconds(2);
    		temp = digitalRead(datapin);

    		if(temp) {
      			pinstate = 1;
      			datain = datain | (1 << i);
    		}
    		else {
			pinstate = 0;
		}

    		digitalWrite(clockpin, 1);
    }
    return datain;
}

void Sensor::set(int latchpin, int datapin, int clockpin) {
	_latchpin = latchpin;
	_datapin = datapin;
	_clockpin = clockpin;

	pinMode(_latchpin, OUTPUT);
	pinMode(_clockpin, OUTPUT); 
	pinMode(_datapin, INPUT);

	digitalWrite(_latchpin, LOW);
	delayMicroseconds(5);
	digitalWrite(_latchpin, HIGH);

	_sensor = ShiftIn(_datapin, _clockpin);
}

int Sensor::check(int i) {
	digitalWrite(_latchpin, LOW);
	delayMicroseconds(5);
	digitalWrite(_latchpin, HIGH);

	_sensor = ShiftIn(_datapin, _clockpin);

	switch(i) {
		case 0:
		if (_sensor&0x01) return 0;
		break;

		case 1:
		if (_sensor&0x02) return 1;
		break;

		case 2:
		if (_sensor&0x04) return 2;
		break;

		case 3:
		if (_sensor&0x08) return 3;
		break;

		case 4:
		if (_sensor&0x10) return 4;
		break;

		case 5:
		if (_sensor&0x20) return 5;
		break;

		case 6:
		if (_sensor&0x40) return 6;
		break;

		case 7:
		if (_sensor&0x80) return 7;
		break;
	}

	return -1;
	delay(20);
}

void Sensor::printStatus(byte value) {
	for(int i = 0; i <= 7; ++i) {
		if((value >> i) & 1)
		    Serial.print(1);
		else
			Serial.print(0);
	}
}

void Sensor::print() {

}



