#include "DelayMode.h"

DelayMode::DelayMode(Nikon* cam) {
	this->camera = cam;
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
 */
void DelayMode::update() {
	if (this->isWaitingForTime() && this->hasDelayPassed()) {
		Serial.print("SHUTTER\n");
		this->camera->shutterNow();
		this->setFired();
	}
}

/*
 * Called when an action is requested
 */
void DelayMode::onAction() {
	this->startDelay();
}

/**
 * Cleanup after running the delay mode
 * There is nothing to clean up, so no-op
 */
void DelayMode::end() {
	//void
}
