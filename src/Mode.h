#ifndef Mode_h
#define Mode_h

#include "Arduino.h"
#include <multiCameraIrControl.h>
#include <Arduino_Vector.h>
#include "Pins.h"

#define SETTINGS_MILLIS_DELAY 0

/**
 * Abstact mode class
 * Parent for any modes we need while taking pictures
 */
class Mode
{
	public:

		/**
		 * Constructor used to set vars for shared delay mode
		 */
		Mode() {
			this->settings.push_back(0);
			this->waitingForTime = false;
		}

		/**
		 * Returns the name of the mode for display purposes
		 */
		virtual char *getName() = 0;

		/**
		 * Called when we first enter a mode
		 */
		virtual void initialize() = 0;

		/**
		 * Called while a mode is being run
		 */
		virtual void update() = 0;

		/**
		 * Called when a mode should clean up after itself
		 */
		virtual void end() = 0;

		/*
		 * Called when the action button is pressed
		 */
		virtual void onAction() = 0;

		/*
		 * Allows a class to have settings
		 */
		bool setSetting(int idx, int value) {
			if (this->settings.size() <= idx) {
				return false;
			}
			settings[idx] = value;
		}

		/*
		 * Initializes settings vector with count elements
		 */
		void initializeSettings(int count) {
			for (int i = 0; i < count; i++) {
				this->settings.push_back(0);
			}
		}

		/**
		 * Prints the current settings of this mode, if any
		 */
		void printSettings() {
			for (int i = 0; i < this->settings.size(); i++) {
				Serial.print(i);
				Serial.print(":");
				Serial.print(this->settings[i]);
				Serial.print(";");
			}
			Serial.print("\n");
		}

		/**
		 * Whether we are waiting for time to elapse
		 * This means we did request action, but are waiting for the configured delay to pass
		 */
		bool isWaitingForTime() {
			return this->waitingForTime;
		}

		/**
		 * Checks if the configured delay has passed for action
		 */
		bool hasDelayPassed() {
			return millis() - this->startMillis >= this->settings[SETTINGS_MILLIS_DELAY];
		}

		/**
		 * Starts counting a delay after shutter request
		 */
		void startDelay() {
			this->startMillis = millis();
			this->waitingForTime = true;
		}

		/**
		 * Tells us we've fired shutter so we're no longer waiting for time
		 */
		void setFired() {
			this->waitingForTime = false;
		}
	protected:
		// Vector that stores our settings
		Vector<int> settings;

	private:
		// The start time, from when we started counting our delay
		unsigned long startMillis;

		// Whether we are waiting for the time to pass before we trigger the camera
		bool waitingForTime;
};
#endif
