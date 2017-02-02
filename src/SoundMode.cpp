#include "SoundMode.h"

/**
 * Constructor
 */
SoundMode::SoundMode(Nikon* cam) {
	this->camera = cam;
}

/**
 * Initialize the sound mode
 */
char *SoundMode::getName() {
	return "Sound";
}

/**
 * Initialize the sound mode
 */
void SoundMode::initialize() {
	this->reset();
}

/**
 * Reset the soundmode to it's start state
 */
void SoundMode::reset() {
	this->listening = true;
}

/**
 * Update the sound mode
 * No-op since the mode is not doing anything
 */
void SoundMode::update() {
	bool hasSound = !digitalRead(SOUND_SENSOR_PIN);

	// If we're waiting for delay to pass, and the delay has passed
	// Fire the shutter
	if (this->isWaitingForTime() && this->hasDelayPassed()) {
		Serial.print("SHUTTER\n");
		this->setFired();
	}

	// If the light difference is more than 10%, we want to shutter
	if (this->listening && hasSound) {
		this->listening = false;
		this->startDelay();
	}
}

/*
 * Called when an action is requested
 */
void SoundMode::onAction() {
	this->reset();
}

/**
 * Cleanup after running the sound mode
 * There is nothing to clean up, so no-op
 */
void SoundMode::end() {
}
