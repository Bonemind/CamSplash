#include "Arduino.h"
#include <multiCameraIrControl.h>
/* Raw IR decoder sketch!
	This sketch/program uses the Arduno and a PNA4602 to
	decode IR received. This can be used to make a IR receiver
	(by looking for a particular code)
	or transmitter (by pulsing an IR LED at ~38KHz for the
	durations detected
	Code is public domain, check out www.ladyada.net and adafruit.com
	for more tutorials!
	*/

// We need to use the 'raw' pin reading methods
// because timing is very important here and the digitalRead()
// procedure is slower!
//uint8_t IR_SENSOR_PIN = 2;
// Digital pin #2 is the same as Pin D2 see
// http://arduino.cc/en/Hacking/PinMapping168 for the 'raw' pin mapping
#define IR_SENSOR_PIN_PIN PIND
#define IR_SENSOR_PIN 11
#define LEDpin 7
// for MEGA use these!
//#define IR_SENSOR_PIN_PIN PINE
//#define IR_SENSOR_PIN 4

// the maximum pulse we'll listen for - 65 milliseconds is a long time
#define MAXPULSE 65000

// what our timing resolution should be, larger is better
// as its more 'precise' - but too large and you wont get
// accurate timing
#define RESOLUTION 20

// we will store up to 100 pulse pairs (this is -a lot-)
uint16_t pulses[100][2]; // pair is high and low pulse
uint8_t currentpulse = 0; // index for pulses we're storing

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

