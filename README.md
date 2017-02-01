#CamSplash

An arduino project meant to help me trigger a photo on my dslr at the correct time.

This is mostly meant for splash or other tight timed zoomed in photography.

Built with platformio.

TODO:

	* Add schematics
	* Configureable delay
	* UI?
	* Timelapse
	* Lightning mode
	* Audio triggered

### Definitions

Action button: Button that tells mode to start doing it's thing, take a picture for the remote mode for example
Mode button: The button used to switch between modes

### Serial protocol

The serial protocol is very simple
Every command and reply is terminated by a single newline
Supported commands are:
	* CURRENTMODE -> Returns the int index of the mode we're currently in
	* CURRENTSETTINGS -> Returns the current settings in format set1:value;set2:value;\n
	* CONFIGURE idx value -> Sets setting with idx to value
	* MODE idx -> Switch to mode with index idx
	* ACTION -> Tells mode to start it's work
