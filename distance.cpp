
#include "distance.h"

void DistanceSensor::begin() {
	pinMode(triggerPin, OUTPUT);
	digitalWrite(triggerPin, LOW);
	pinMode(echoPin, INPUT);
}

void DistanceSensor::update() {
	distance = getDistance(true);
}

int16_t DistanceSensor::getDistance(bool immediate) {
	if (immediate) {
		digitalWrite(triggerPin, HIGH);
		delayMicroseconds(10);
		digitalWrite(triggerPin, LOW);
		uint32_t pulseTime = pulseIn(echoPin, HIGH);
		return pulseTime / 58; // Laut Datenblatt
	} else {
		return distance;
	}
}