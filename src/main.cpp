#include "Arduino.h"
#include "Mode.h"
#include "RemoteMode.h"
#include "DelayMode.h"
#include "IRMode.h"
#include "LaserMode.h"
#include <multiCameraIrControl.h>
#include "Pins.h"

#define MODECOUNT 4

// The last state the ir-led was in, true if visible, false if not visible
bool lastState = false;
int modeIdx = 0;

bool prevModeButtonState = false;
bool prevActionButtonState = false;

// The camera object, used to control the camera
Nikon nikon(CAMERA_CONTROL_PIN);

/**
 * The stage we are currently in
 */
Mode* currentMode;

// Initial applcation setup
void setup(void) {
	// Setup serial communication
	Serial.begin(9600);

	// Feedback
	Serial.println("Ready");

	// Set pins in correct modes
	pinMode(IRMODE_LED_PIN, OUTPUT);
	pinMode(IR_SENSOR_PIN, INPUT);
	pinMode(FEEDBACKPIN, OUTPUT);
	pinMode(CAMERA_CONTROL_PIN, OUTPUT);
	pinMode(LASER_PIN, OUTPUT);
	pinMode(MODE_BUTTON_PIN, INPUT_PULLUP);
	pinMode(ACTION_BUTTON_PIN, INPUT_PULLUP);
	pinMode(PLUS_BUTTON_PIN, INPUT_PULLUP);
	pinMode(MINUS_BUTTON_PIN, INPUT_PULLUP);

	// Set pins to low, just so we have a known start state
	digitalWrite(IRMODE_LED_PIN, LOW);
	digitalWrite(CAMERA_CONTROL_PIN, LOW);
	digitalWrite(FEEDBACKPIN, LOW);
	digitalWrite(IR_SENSOR_PIN, LOW);

	// Initialize mode
	currentMode = new RemoteMode(&nikon);
	currentMode->initialize();
}

void nextMode() {
	// Determine number of next mode
	modeIdx = (modeIdx + 1) % MODECOUNT;
	// Tell current mode to end
	currentMode->end();

	// Resolve number to mode
	switch (modeIdx){
		case 0:
			currentMode = new RemoteMode(&nikon);
			break;
		case 1:
			currentMode = new DelayMode(&nikon);
			break;
		case 2:
			currentMode = new IRMode(&nikon);
			break;
		case 3:
			currentMode = new LaserMode(&nikon);
			break;
	}
	currentMode->initialize();
}

void loop() {
	// Determine when we're trying to switch modes
	// Inverted because pullup
	bool modeButtonPressed = !digitalRead(MODE_BUTTON_PIN);

	if (modeButtonPressed && !prevModeButtonState) {
		nextMode();
		Serial.print(currentMode->getName());
		Serial.print("\n");
	}
	prevModeButtonState = modeButtonPressed;


	bool actionButtonPressed = !digitalRead(ACTION_BUTTON_PIN);
	if (actionButtonPressed && !prevActionButtonState) {
		currentMode->onAction();
	}
	prevActionButtonState = actionButtonPressed;

	// Run mode
	currentMode->update();
}
