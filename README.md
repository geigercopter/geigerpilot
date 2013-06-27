geigerpilot
===========
Work in progress - IN VERY EARLY ALPHA - Use at your own risks

GeigerPilot is the flight controller firmware for the GeigerCopter projet. 

The base project is adding radiation measurement features to a multicopter drone. Basically, its adding a geiger counter on a quadcopter !

It's intended to work on CRUIS AIOP V2 arduino based flight controller.

The project is a fork of alternative firmware named MegaPirateNG, a port of ardupilot firmware https://github.com/diydrones/ardupilot designed to work on alternative flight controllers, other than official DIYDrone / 3DRobotics FC boards.

MegaPirateNG 2.9 R7 (ArduCopter 2.9.1) sources can be found at google code repository :

http://code.google.com/p/megapirateng/source/browse/beta/2.9.1/

Unlike MegaPirateNG, GeigerPilot will support only CRIUS AIOP V1 and V2 flight controller.

Also, some features, unsupported by MegaPirateNG but working on ArduPilot, will be reintroduced.

- Maxbotix sonars
- ADNS-3080 Optical flow

Support of DYP-ME007 Ultrasonic range finder has been removed, as this require interruption handling of PCINT0 we also need for catching geiger counter pulses. As, in our early prototypes, maxbotix is used, we removed the drivers.

One thing MegaPirateNG doesnt support on CRIUS AIOP V2 is mixing optical flow sensor with data logger. As we need both, we'll reimplement this feature.

GeigerCounter library is intended to be portable and will be proposed for update on the original ArduPilot project repository.

Also, il will be modified to support a wider range of radiation measurement sensors, not only the actual SafeCast "AllanL" High Voltage Power Supply (HPVS) on SMB-20 geiger-müller tube.

