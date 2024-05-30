
#include "dibse.h"



DibsE::DibsE()
	: rgbLED(1, RGB_LED_PIN, NEO_GRB + NEO_KHZ800),
	  distanceSensor(DISTANCE_TRIGGER_PIN, DISTANCE_ECHO_PIN),
	  ledMatrix(LED_LATCH,LED_DATA,LED_CLOCK)
	  {}

void DibsE::setup() {
	// Initialisiert das RGB-LED
	rgbLED.begin();
	distanceSensor.begin();
}

void DibsE::loop() {
	uint32_t now = millis();
	if (blinkOn) {
		if (now - lastBlinkTime >= duration) {
			if (rgbLedOn) {
				rgbLED.setPixelColor(0, 0, 0, 0);
			} else {
				rgbLED.setPixelColor(0, red, green, blue);
			}
			rgbLED.show();
			rgbLedOn = !rgbLedOn;
			lastBlinkTime = now;
		}
	}
	if (now - lastDistanceTime >= DISTANCE_MEASURE_INTERVAL) {
		distanceSensor.update();
		auto distance = distanceSensor.getDistance();
		Serial.print("Distance = ");
		Serial.print(distance);
		Serial.println(" cm");
		lastDistanceTime = now;
		uint8_t red = 0;
		uint8_t green = 0;
		if (distance < 60) {
			red = 200;
			green = 0;
		} else {
			red = 0;
			green = 200;
		}
		simpleBlinkOn(map(distance, 0, 400, 100, 1000), red, green, 0);
		distanceBufferStart--;
		if (distanceBufferStart < 0) {
			distanceBufferStart = 8 + distanceBufferStart;
		}
		distanceBuffer[distanceBufferStart] = distance;
	}
	// Clears the display buffer.
	ledMatrix.clear();
	// Draws the display
	for (int8_t x = 0; x < 8; x++) {
		auto dist = distanceBuffer[(distanceBufferStart + x)%8];
		int8_t nrpixel = 8 - dist/10;
		if (nrpixel < 0) {
			nrpixel = 0;
		}
		for (int8_t y = 0; y < nrpixel; y++) {
			ledMatrix.drawPixel(x, y, true);
		}
	}
	// Display everything on the display.
	ledMatrix.update();
}

void DibsE::simpleBlinkOn(int duration, int red, int green, int blue) {
	blinkOn = true;
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->duration = duration;
}

void DibsE::simpleBlinkOff() {
	blinkOn = false;
}