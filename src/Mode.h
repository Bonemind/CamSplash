#ifndef Mode_h
#define Mode_h

#include "Arduino.h"
#include <multiCameraIrControl.h>
#include <Arduino_Vector.h>
#include "Pins.h"

/**
 * Abstact mode class
 * Parent for any modes we need while taking pictures
 */
class Mode
{
	public:

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

	protected:
		// Vector that stores our settings
		Vector<int> settings;
};
#endif
