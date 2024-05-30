
#ifndef DISTANCE_H_
#define DISTANCE_H_

#include <Arduino.h>

class DistanceSensor {
public:
	DistanceSensor(uint8_t triggerPin, uint8_t echoPin)
		: triggerPin(triggerPin), echoPin(echoPin) {}

	void begin();
	void update();
	int16_t getDistance(bool immediate = false);

private:
	uint8_t triggerPin;
	uint8_t echoPin;
	int16_t distance = 0;
};

#endif /* DISTANCE_H_ */