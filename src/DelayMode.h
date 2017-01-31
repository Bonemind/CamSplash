#ifndef DelayMode_h
#define DelayMode_h

#include "Mode.h"

/**
 * Defines the delay mode as a child of Mode
 */
class DelayMode : public Mode
{
	public:
		DelayMode(Nikon* cam);
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
		bool wasPressed;
};

#endif
