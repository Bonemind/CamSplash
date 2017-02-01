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



	private:
		Nikon* camera;
		bool lastState;
		int startMillis;
		int lightValue;
		bool listening = false;
		const int CALIBRATION_DELAY = 1000;

		/**
		 * Resets the mode to it's original state
		 */
		void reset();
};

#endif
