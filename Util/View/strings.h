#ifndef RADIOCONTROLSOFTWARE_STRINGS_H
#define RADIOCONTROLSOFTWARE_STRINGS_H

#include <avr/pgmspace.h>

#define TR(x) string_get(x),12

static const char string_back[] PROGMEM = "Back";
static const char string_armDisarm[] PROGMEM = "Arm/Disarm";
static const char string_flightmodes[] PROGMEM = "Flightmodes";
static const char string_downlink[] PROGMEM = "Downlink";
static const char string_channelMapping[] PROGMEM = "Channel Map";
static const char string_settings[] PROGMEM = "Settings";
static const char string_debug[] PROGMEM = "Debug";
static const char string_calibrate0[] PROGMEM = "Move the";
static const char string_calibrate1[] PROGMEM = "Joysticks!";
static const char string_button[] PROGMEM = "Button (";
static const char string_finish[] PROGMEM = "Finish";
static const char string_calibrate[] PROGMEM = "Calibrate";
static const char string_disableUSB[] PROGMEM = "Disable USB";
static const char string_enableUSB[] PROGMEM = "Enable USB";
static const char string_disableLora[] PROGMEM = "Disable LoRa";
static const char string_enableLora[] PROGMEM = "Enable Lora";
static const char string_log[] PROGMEM = "Log";
static const char string_compiledOn[] PROGMEM = "Compiled On";
static const char string_leftJoy[] PROGMEM = "Left Joy";
static const char string_rightJoy[] PROGMEM = "Right Joy";
static const char string_xAxis[] PROGMEM = "X-Axis (";
static const char string_yAxis[] PROGMEM = "Y-Axis (";
static const char string_fmode[] PROGMEM = "F-Mode (";
static const char string_armed[] PROGMEM = "Armed (";
static const char string_next[] PROGMEM = "Next";
static const char string_previous[] PROGMEM = "Previous";
static const char string_empty[] PROGMEM = "";
static const char string_land[] PROGMEM = "Land";
static const char string_angle[] PROGMEM = "Angle";
static const char string_hold[] PROGMEM = "Hold";
static const char string_waypoint[] PROGMEM = "Waypoint";
static const char string_launch[] PROGMEM = "Launch";
static const char string_compileTime[] PROGMEM = __TIME__;
static const char string_compileDate[] PROGMEM = __DATE__;
static const char string_version[] PROGMEM = "0.1.1-AVR";
static const char string_snr[] PROGMEM = "SNR: ";
static const char string_rssi[] PROGMEM = "RSSI: ";
static const char string_sent[] PROGMEM = "Sent: ";
static const char string_received[] PROGMEM = "Recv: ";
static const char string_receivedData[] PROGMEM = "Data";

char* string_get(const char *addr);

#endif //RADIOCONTROLSOFTWARE_STRINGS_H
