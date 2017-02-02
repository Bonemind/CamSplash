#include "RemoteMode.h"


RemoteMode::RemoteMode(Nikon* cam) {
	this->camera = cam;
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
	// Void
}

/*
 * Called when an action is requested
 */
void RemoteMode::onAction() {
	Serial.print("SHUTTER\n");
	this->camera->shutterNow();
}

/**
 * Cleanup after running the remote mode
 * There is nothing to clean up, so no-op
 */
void RemoteMode::end() {
	//void
}
