#include "DelayMode.h"

DelayMode::DelayMode(Nikon* cam) {
	this->camera = cam;
	this->wasPressed = false;
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
 * TODO: Actually add possibility to delay
 */
void DelayMode::update() {
	bool isPressed = !digitalRead(ACTION_BUTTON_PIN);
	if (isPressed && !this->wasPressed) {
		Serial.print("SHUTTER\n");
	}
	this->wasPressed = isPressed;
}

/**
 * Cleanup after running the delay mode
 * There is nothing to clean up, so no-op
 */
void DelayMode::end() {
	//void
}
