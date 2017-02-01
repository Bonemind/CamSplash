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
 * No-op since the mode is not doing anything
 * TODO: Actually add possibility to delay
 */
void DelayMode::update() {
	// Void
}

/*
 * Called when an action is requested
 */
void DelayMode::onAction() {
	// TODO: Make use delay
}

/**
 * Cleanup after running the delay mode
 * There is nothing to clean up, so no-op
 */
void DelayMode::end() {
	//void
}
