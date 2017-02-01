#ifndef IRMode_h
#define IRMode_h

#include "Mode.h"

/**
 * Defines the ir mode as a child of Mode
 */
class IRMode : public Mode
{
	public:
		IRMode(Nikon* cam);
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
		Nikon* camera;
		bool lastState;

		void pulseIR();
};

#endif
