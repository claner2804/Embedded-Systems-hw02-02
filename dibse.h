
#ifndef DIBSE_H_
#define DIBSE_H_

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "distance.h"
#include "LedMatrix.h"

#define RGB_LED_PIN 			A4
#define DISTANCE_TRIGGER_PIN	8
#define DISTANCE_ECHO_PIN		4

// LED Matrix pins
#define LED_LATCH 11
#define LED_DATA 16
#define LED_CLOCK 15

#define DISTANCE_MEASURE_INTERVAL	500


class DibsE {
public:
	DibsE();
	void setup();
	void loop();

	void simpleBlinkOn(int duration, int red, int green, int blue);
	void simpleBlinkOff();

private:
	Adafruit_NeoPixel rgbLED;
	DistanceSensor distanceSensor;
	LedMatrix ledMatrix;
	bool blinkOn = false;
	bool rgbLedOn = false;
	int red = 0;
	int green = 0;
	int blue = 0;
	int duration = 0;
	uint32_t lastBlinkTime = 0;
	uint32_t lastDistanceTime = 0;
	int16_t distanceBuffer[8] = {0};
	int8_t distanceBufferStart = 0;
};

#endif /* DIBSE_H_ */