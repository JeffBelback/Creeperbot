#ifndef PingSensor_H
#define PingSensor_H

#include "Arduino.h"
#include "pins_arduino.h"

class PingSensor {
public:
	PingSensor();
	~PingSensor();
        long determineDistanceInInches();
	long microsecondsToInches(long microseconds);
};
#endif
