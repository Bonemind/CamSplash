#include "RemoteMode.h"


RemoteMode::RemoteMode(Nikon* cam) {
	this->camera = cam;
	this->wasPressed = false;
}

/**
 * Initialize the remote mode
 */
char *RemoteMode::getName() {
	return "Remote";
}

/**
 * Initialize the remote mode
 */
void RemoteMode::initialize() {
	//Void
}

/**
 * Update the remote mode
 * No-op since the mode is not doing anything
 */
void RemoteMode::update() {
	bool isPressed = !digitalRead(ACTION_BUTTON_PIN);
	if (isPressed && !this->wasPressed) {
		Serial.print("SHUTTER\n");
	}
	this->wasPressed = isPressed;
}

/**
 * Cleanup after running the remote mode
 * There is nothing to clean up, so no-op
 */
void RemoteMode::end() {
	//void
}
