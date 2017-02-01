#ifndef LaserMode_h
#define LaserMode_h

#include "Mode.h"

/**
 * Defines the laser mode as a child of Mode
 */
class LaserMode : public Mode
{
	public:
		LaserMode(Nikon* cam);
		/**
		 * Startup of the mode
		 */
		char *getName();

		/**
		 * Startup of the mode
		 */
		void initialize();

		/**
		 * Update during mode running
		 */
		void update();

		/**
		 * Cleanup after the mode was completed
		 */
		void end();

		/*
		 * Called when the action button is pressed
		 */
		void onAction();

	private:
		// How long to average the light value before we start listening for shutter
		const unsigned long CALIBRATION_DELAY = 1000;

		// The reference to the camera object
		Nikon* camera;

		// The time this iteration of waiting for the laser started
		unsigned long startMillis;

		// The current (averaged) light value
		int lightValue;

		// Whether we are actually listening to trigger shutter or not
		bool listening = false;

		/**
		 * Resets the mode to it's original state
		 */
		void reset();
};

#endif
