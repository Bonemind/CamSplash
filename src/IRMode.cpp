#include "IRMode.h"


IRMode::IRMode(Nikon* cam) {
	this->camera = cam;
	this->lastState = false;
}

/**
 * Initialize the ir mode
 */
char *IRMode::getName() {
	return "IR";
}

/**
 * Initialize the ir mode
 */
void IRMode::initialize() {
	//Void
}

/**
 * Update the ir mode
 * No-op since the mode is not doing anything
 */
void IRMode::update() {
	// Pulse the led so the reciever can detect it
	this->pulseIR();

	// Read the led state, if low then the led is visible
	bool currState = digitalRead(IR_SENSOR_PIN) == LOW;

	// The led just became visible, or invisible
	// Trigger camera shutter
	if (currState != lastState) {
		if (currState) {
			Serial.print("On");
		} else {
			Serial.print("Off");
		}
	}

	// Store last state
	lastState = currState;
}

// Puls led for 38khz reciever
void IRMode::pulseIR() {
	for(int i = 0; i <= 384; i++) {
		digitalWrite(IRMODE_LED_PIN, HIGH);
		delayMicroseconds(13);
		digitalWrite(IRMODE_LED_PIN, LOW);
		delayMicroseconds(13);
	}
}

/*
 * Called when an action is requested
 */
void IRMode::onAction() {
	//TODO: Something
}

/**
 * Cleanup after running the ir mode
 * There is nothing to clean up, so no-op
 */
void IRMode::end() {
	//void
}
