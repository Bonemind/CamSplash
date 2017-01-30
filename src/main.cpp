#include "Arduino.h"
#include <multiCameraIrControl.h>

// Prelimenary sketch
// Waits for the IR sensor to switch to either on or off, then triggers the
// IR led that controls the camera to take a picture
// TODO: Cleanup code, add delay
#define IR_SENSOR_PIN_PIN PIND
#define IR_SENSOR_PIN 11
#define LEDpin 7
#define FEEDBACKPIN 10
#define CAMERA_CONTROL_PIN 9

// The last state the ir-led was in, true if visible, false if not visible
bool lastState = false;

// The camera object, used to control the camera
Nikon nikon(CAMERA_CONTROL_PIN);

// Initial applcation setup
void setup(void) {
	// Setup serial communication
	Serial.begin(9600);

	// Feedback
	Serial.println("Ready");

	// Set pins in correct modes
	pinMode(LEDpin, OUTPUT);
	pinMode(IR_SENSOR_PIN, INPUT);
	pinMode(FEEDBACKPIN, OUTPUT);
	pinMode(CAMERA_CONTROL_PIN, OUTPUT);

	// Set pins to low, just so we have a known start state
	digitalWrite(LEDpin, LOW);
	digitalWrite(CAMERA_CONTROL_PIN, LOW);
	digitalWrite(FEEDBACKPIN, LOW);
	digitalWrite(IR_SENSOR_PIN, LOW);
}

// Puls led for 38khz reciever
void IR38Write() {
	for(int i = 0; i <= 384; i++) {
		digitalWrite(LEDpin, HIGH);
		delayMicroseconds(13);
		digitalWrite(LEDpin, LOW);
		delayMicroseconds(13);
	}
}

// Meat and bones of the application
void loop(void) {
	// Pulse the led so the reciever can detect it
	IR38Write();

	// Read the led state, if low then the led is visible
	bool currState = digitalRead(IR_SENSOR_PIN) == LOW;

	// The led just became visible, or invisible
	// Trigger camera shutter
	if (currState != lastState) {
		nikon.shutterNow();
		if (currState) {
			Serial.print("On");
			digitalWrite(FEEDBACKPIN, HIGH);
		} else {
			Serial.print("Off");
			digitalWrite(FEEDBACKPIN, LOW);
		}
	}

	// Store last state
	lastState = currState;

	delay(50);
}

