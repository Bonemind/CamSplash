#ifndef SoundMode_h
#define SoundMode_h

#include "Mode.h"

/**
 * Defines the sound mode as a child of Mode
 */
class SoundMode : public Mode
{
	public:
		SoundMode(Nikon* cam);
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
		// The reference to the camera object
		Nikon* camera;

		// Whether we are actually listening to trigger shutter or not
		bool listening = false;

		/**
		 * Resets the mode to it's original state
		 */
		void reset();
};

#endif
