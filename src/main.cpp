#include "Arduino.h"
#include "Mode.h"
#include "RemoteMode.h"
#include "DelayMode.h"
#include "IRMode.h"
#include <multiCameraIrControl.h>
#include "Pins.h"

#define MODECOUNT 3

// Prelimenary sketch
// Waits for the IR sensor to switch to either on or off, then triggers the
// IR led that controls the camera to take a picture
// TODO: Cleanup code, add delay

// The last state the ir-led was in, true if visible, false if not visible
bool lastState = false;
int modeIdx = 0;

bool lastButtonState = false;

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
	}
	currentMode->initialize();
}

void loop() {
	// Determine when we're trying to switch modes
	// Inverted because pullup
	bool buttonpressed = !digitalRead(MODE_BUTTON_PIN);

	if (buttonpressed && !lastButtonState) {
		nextMode();
		Serial.print(currentMode->getName());
		Serial.print("\n");
		digitalWrite(2, HIGH);
	} else {
		digitalWrite(2, LOW);
	}

	lastButtonState = buttonpressed;


	// Run mode
	currentMode->update();
}
