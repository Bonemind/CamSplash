#include "Arduino.h"
#include <multiCameraIrControl.h>

// Prelimenary sketch
// Waits for the IR sensor to switch to either on or off, then triggers the
// IR led that controls the camera to take a picture
// TODO: Cleanup code, add delay
#define IR_SENSOR_PIN_PIN PIND
#define IR_SENSOR_PIN 11
#define LEDpin 7

bool lastState = false;
const int FEEDBACKPIN = 10;
const int CAMERA_CONTROL_PIN = 9;

Nikon nikon(CAMERA_CONTROL_PIN);

void setup(void) {
	Serial.begin(9600);
	Serial.println("Ready to decode IR!");
	pinMode(LEDpin, OUTPUT);
	pinMode(IR_SENSOR_PIN, INPUT);
	pinMode(FEEDBACKPIN, OUTPUT);
	pinMode(CAMERA_CONTROL_PIN, OUTPUT);
	digitalWrite(LEDpin, LOW);
	digitalWrite(CAMERA_CONTROL_PIN, LOW);
	digitalWrite(FEEDBACKPIN, LOW);
	digitalWrite(IR_SENSOR_PIN, LOW);
}

void IR38Write() {
	for(int i = 0; i <= 384; i++) {
		digitalWrite(LEDpin, HIGH);
		delayMicroseconds(13);
		digitalWrite(LEDpin, LOW);
		delayMicroseconds(13);
	}
}

void loop(void) {
	IR38Write();
	bool currState = digitalRead(IR_SENSOR_PIN) == LOW;
	if (currState != lastState) {
		Serial.print("---------------------\n");
		Serial.print("Change\n");
		nikon.shutterNow();
		if (currState) {
			Serial.print("Now on\n");
			digitalWrite(FEEDBACKPIN, HIGH);
		} else {
			Serial.print("Now off\n");
			digitalWrite(FEEDBACKPIN, LOW);
		}
	}
	lastState = currState;
	delay(50);
}

