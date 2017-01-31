#ifndef RemoteMode_h
#define RemoteMode_h

#include "Mode.h"

/**
 * Defines the remote mode as a child of Mode
 */
class RemoteMode : public Mode
{
	public:
		RemoteMode(Nikon* cam);
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
