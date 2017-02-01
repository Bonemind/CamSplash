#include "LaserMode.h"


LaserMode::LaserMode(Nikon* cam) {
	this->camera = cam;
	this->lastState = false;
}

/**
 * Initialize the laser mode
 */
char *LaserMode::getName() {
	return "Laser";
}

/**
 * Initialize the laser mode
 */
void LaserMode::initialize() {
	this->reset();
}

/**
 * Reset the lasermode to it's start state
 */
void LaserMode::reset() {
	this->lightValue = analogRead(LASER_SENSOR_PIN);
	this->startMillis = millis();
	digitalWrite(LASER_PIN, HIGH);
	this->listening = false;
}

/**
 * Update the laser mode
 * No-op since the mode is not doing anything
 */
void LaserMode::update() {
	// Get current reading
	int currReading = analogRead(LASER_SENSOR_PIN);

	// Get Different with previous reading
	int diff = this->lightValue - currReading;
	diff = abs(diff);


	// Check if we want to reset (start listening again)
	bool currState = !digitalRead(ACTION_BUTTON_PIN);
	if (currState && currState != lastState) {
		this->reset();
	}
	lastState = currState;

	// Check if we're past calibration time, if so, set listening
	if (this->startMillis + this->CALIBRATION_DELAY > millis()) {
		this->listening = true;
	}

	if (this->listening) {
		Serial.print(currReading);
		Serial.print(" : ");
		Serial.print(this->lightValue);
		Serial.print("\n");
	}

	// If the light difference is more than 10%, we want to shutter
	if (this->listening && (diff > 0.1 * this->lightValue)) {
		digitalWrite(LASER_PIN, LOW);
		this->listening = false;
		Serial.print("SHUTTER\n");
	}

	// Average lightvalue
	this->lightValue = (currReading + this->lightValue) / 2;
}

/**
 * Cleanup after running the laser mode
 * There is nothing to clean up, so no-op
 */
void LaserMode::end() {
	digitalWrite(LASER_PIN, LOW);
}
