#ifndef Mode_h
#define Mode_h

#include "Arduino.h"
#include <multiCameraIrControl.h>
#include "Pins.h"

/**
 * Abstact mode class
 * Parent for any modes we need during roasting
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
};
#endif
