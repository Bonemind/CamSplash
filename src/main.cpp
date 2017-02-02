#include "Arduino.h"
#include "Mode.h"
#include "RemoteMode.h"
#include "DelayMode.h"
#include "IRMode.h"
#include "LaserMode.h"
#include "SoundMode.h"
#include <multiCameraIrControl.h>
#include <SoftwareSerial.h>
#include <SerialCommand.h>
#include "Pins.h"

#define MODECOUNT 4

// The last state the ir-led was in, true if visible, false if not visible
bool lastState = false;
int modeIdx = 0;

bool prevModeButtonState = false;
bool prevActionButtonState = false;

SerialCommand serialCommand;

// The camera object, used to control the camera
Nikon nikon(CAMERA_CONTROL_PIN);

/**
 * The stage we are currently in
 */
Mode* currentMode;

//--------------------------------------------------------------------------------
//MODE HANDLING
//--------------------------------------------------------------------------------
void setMode(int idx) {
	// Tell current mode to end
	currentMode->end();

	// Resolve number to mode
	switch (idx){
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
		case 4:
			currentMode = new SoundMode(&nikon);
			break;
	}
	currentMode->initialize();

	Serial.print(currentMode->getName());
	Serial.print("\n");
}

void nextMode() {
	// Determine number of next mode
	modeIdx = (modeIdx + 1) % MODECOUNT;
	setMode(modeIdx);
}

//--------------------------------------------------------------------------------
//SERIAL COMMAND HANDLING METHODS
//--------------------------------------------------------------------------------
/**
 * Fetches a setting index and value from serial input, parses them to int, then
 * sets it in the current mode
 */
void configureSetting() {
	int settingIdx;
	int value;
	char *arg;

	arg = serialCommand.next();
	if (arg != NULL)
	{
		settingIdx = atoi(arg);    // Converts a char string to an integer
	}
	else {
		Serial.println("No arguments");
		return;
	}

	arg = serialCommand.next();
	if (arg != NULL)
	{
		value = atol(arg);
	}
	else {
		Serial.println("No second argument");
		return;
	}

	Serial.print(settingIdx);
	Serial.print(":");
	Serial.print(value);
	Serial.print("\n");
	currentMode->setSetting(settingIdx, value);
}

/**
 * Handles unknown serial commands
 */
void unknownCommand() {
	Serial.print("Unknown command\n");
}

/**
 * Handles action serial command
 */
void actionSerialCommand() {
	currentMode->onAction();
}

/**
 * Handles mode switch serial command
 */
void modeSwitchSerialCommand() {
	char *arg;

	arg = serialCommand.next();
	if (arg != NULL)
	{
		modeIdx = atoi(arg);    // Converts a char string to an integer
	}
	else {
		Serial.println("No arguments");
		return;
	}
	setMode(modeIdx);
}

/**
 * Returns the current mode index
 */
void modeRequestSerialCommand() {
	Serial.print(modeIdx);
	Serial.print("\n");
}

/**
 * Returns the current settings
 */
void settingsRequestSerialCommand() {
	currentMode->printSettings();
}

// Initial applcation setup
void setup(void) {
	// Setup serial communication
	Serial.begin(9600);

	// Feedback
	Serial.println("Ready");

	// SerialCommand setup
	serialCommand.addCommand("ACTION", actionSerialCommand);
	serialCommand.addCommand("CONFIGURE", configureSetting);
	serialCommand.addCommand("MODE", modeSwitchSerialCommand);
	serialCommand.addCommand("CURRENTMODE", modeRequestSerialCommand);
	serialCommand.addCommand("CURRENTSETTINGS", settingsRequestSerialCommand);
	serialCommand.addDefaultHandler(unknownCommand);


	// Set pins in correct modes
	pinMode(IRMODE_LED_PIN, OUTPUT);
	pinMode(IR_SENSOR_PIN, INPUT);
	pinMode(FEEDBACKPIN, OUTPUT);
	pinMode(CAMERA_CONTROL_PIN, OUTPUT);
	pinMode(LASER_PIN, OUTPUT);
	pinMode(MODE_BUTTON_PIN, INPUT_PULLUP);
	pinMode(ACTION_BUTTON_PIN, INPUT_PULLUP);
	pinMode(SOUND_SENSOR_PIN, INPUT);
	pinMode(MINUS_BUTTON_PIN, INPUT_PULLUP);

	// Set pins to low, just so we have a known start state
	digitalWrite(IRMODE_LED_PIN, LOW);
	digitalWrite(CAMERA_CONTROL_PIN, LOW);
	digitalWrite(FEEDBACKPIN, LOW);
	digitalWrite(IR_SENSOR_PIN, LOW);
	digitalWrite(SOUND_SENSOR_PIN, LOW);

	// Initialize mode
	currentMode = new RemoteMode(&nikon);
	currentMode->initialize();
}


void loop() {
	// Determine when we're trying to switch modes
	// Inverted because pullup
	bool modeButtonPressed = !digitalRead(MODE_BUTTON_PIN);
	
	serialCommand.readSerial();

	if (modeButtonPressed && !prevModeButtonState) {
		nextMode();
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

