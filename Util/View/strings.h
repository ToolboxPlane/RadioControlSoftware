#ifndef RADIOCONTROLSOFTWARE_STRINGS_H
#define RADIOCONTROLSOFTWARE_STRINGS_H

#include <avr/pgmspace.h>

#define TR(x) string_get(x),12

static const char string_back[] PROGMEM = "Back";
static const char string_arm_disarm[] PROGMEM = "Arm/Disarm";
static const char string_flightmodes[] PROGMEM = "Flightmodes";
static const char string_telemetry[] PROGMEM = "Telemetry";
static const char string_settings[] PROGMEM = "Settings";
static const char string_debug[] PROGMEM = "Debug";
static const char string_calibrate0[] PROGMEM = "Move the";
static const char string_calibrate1[] PROGMEM = "Joysticks!";
static const char string_calibrate[] PROGMEM = "Calibrate";
static const char string_disable_usb[] PROGMEM = "Disable USB";
static const char string_enable_usb[] PROGMEM = "Enable USB";
static const char string_disable_lora[] PROGMEM = "Disable LoRa";
static const char string_enable_lora[] PROGMEM = "Enable Lora";
static const char string_compiled_on[] PROGMEM = "Compiled On";
static const char string_empty[] PROGMEM = "";
static const char string_land[] PROGMEM = "Land";
static const char string_angle[] PROGMEM = "Angle";
static const char string_hold[] PROGMEM = "Hold";
static const char string_waypoint[] PROGMEM = "Waypoint";
static const char string_launch[] PROGMEM = "Launch";
static const char string_compile_time[] PROGMEM = __TIME__;
static const char string_compile_date[] PROGMEM = __DATE__;
static const char string_version[] PROGMEM = "0.2.0-AVR";
static const char string_snr[] PROGMEM = "SNR: ";
static const char string_snr_remote[] PROGMEM = "R-SNR: ";
static const char string_rssi[] PROGMEM = "RSSI: ";
static const char string_rssi_remote[] PROGMEM = "R-RSSI: ";
static const char string_sent[] PROGMEM = "Sent: ";
static const char string_received[] PROGMEM = "Recv: ";
static const char string_rf_info[] PROGMEM = "RF-Info";
static const char string_channel[] PROGMEM = "Channel ";

char* string_get(const char *addr);

#endif //RADIOCONTROLSOFTWARE_STRINGS_H
