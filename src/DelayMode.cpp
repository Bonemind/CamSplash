#include "DelayMode.h"
#define SETTINGS_MILLIS_DELAY 0

DelayMode::DelayMode(Nikon* cam) {
	this->camera = cam;
	this->waitingForTime = false;
	this->initializeSettings(1);
}

/**
 * Initialize the delay mode
 */
char *DelayMode::getName() {
	return "Delay";
}

/**
 * Initialize the delay mode
 */
void DelayMode::initialize() {
	//Void
}

/**
 * Update the delay mode
 * No-op since the mode is not doing anything
 */
void DelayMode::update() {
	if (!this->waitingForTime) {
		return;
	}

	if (millis() - this->startMillis < this->settings[SETTINGS_MILLIS_DELAY]) {
		return;
	}

	Serial.print("SHUTTER\n");
	this->waitingForTime = false;
}

/*
 * Called when an action is requested
 */
void DelayMode::onAction() {
	this->startMillis = millis();
	this->waitingForTime = true;
}

/**
 * Cleanup after running the delay mode
 * There is nothing to clean up, so no-op
 */
void DelayMode::end() {
	//void
}
