CC=avr-gcc
FLAGS=-std=c++11 -DF_CPU=16000000UL -DARDUINO=169 #Add -Wall
AVR_GCC_MCU=atmega328p

ARDUINO_HARDWARE_FOLDER=~/Programme/arduino-1.6.9/hardware/arduino/avr
AVR_FLASH=avrdude
AVRDUDE_DEVICE=m328p
AVRDUDE_PROGRAMMER=arduino

INPUT_FILES=main.cpp label/label.cpp Joystick.cpp \
	$(wildcard $(ARDUINO_HARDWARE_FOLDER)/cores/arduino/*.cpp) \
	$(wildcard $(ARDUINO_HARDWARE_FOLDER)/cores/arduino/*.c) \
	$(wildcard $(ARDUINO_HARDWARE_FOLDER)/cores/arduino/*.S) \
	$(wildcard $(ARDUINO_HARDWARE_FOLDER)/variants/standard/*.cpp) \
	$(wildcard $(ARDUINO_HARDWARE_FOLDER)/libraries/Wire/src/*.cpp)  \
	$(wildcard $(ARDUINO_HARDWARE_FOLDER)/libraries/Wire/src/utility/*.c)  \
	$(wildcard $(ARDUINO_HARDWARE_FOLDER)/libraries/SPI/src/*.cpp) \
	$(wildcard $(ARDUINO_HARDWARE_FOLDER)/libraries/EEPROM/src/*.cpp) \
	Adafruit_ILI9341/Adafruit_ILI9341.cpp \
	Adafruit_STMPE610/Adafruit_STMPE610.cpp \
	Adafruit-GFX-Library/Adafruit_GFX.cpp \
	$(wildcard RadioHead/*.cpp) \
	RadioControlProtocol/rcLib.cpp	
	#RadioHead/RH_RF95.cpp \
	#RadioHead/RHGenericDriver.cpp \
	#RadioHead/RHSPIDriver.cpp \

HEX_FILE=main.hex

all: build flash

INCLUDE_CORE=-I $(ARDUINO_HARDWARE_FOLDER)/cores/arduino/
INCLUDE_VARIANTS=-I $(ARDUINO_HARDWARE_FOLDER)/variants/standard/
INCLUDE_WIRE=-I $(ARDUINO_HARDWARE_FOLDER)/libraries/Wire/src/
INCLUDE_EEPROM=-I $(ARDUINO_HARDWARE_FOLDER)/libraries/SPI/src/
INCLUDE_SPI=-I $(ARDUINO_HARDWARE_FOLDER)/libraries/EEPROM/src/

INCLUDE_ILI9341=-I Adafruit_ILI9341/
INCLUDE_RADIO_HEAD=-I RadioHead/
INCLUDE_STMPE610=-I Adafruit_STMPE610/
INCLUDE_GFX=-I Adafruit-GFX-Library/

INCLUDE_LIBRARYS=$(INCLUDE_ILI9341) $(INCLUDE_RADIO_HEAD) $(INCLUDE_STMPE610) $(INCLUDE_GFX)

INCLUDE_PATH= $(INCLUDE_CORE) $(INCLUDE_VARIANTS) $(INCLUDE_WIRE) $(INCLUDE_EEPROM) $(INCLUDE_SPI) $(INCLUDE_LIBRARYS)

build:
	$(CC) $(FLAGS) $(INCLUDE_PATH) -mmcu=$(AVR_GCC_MCU) -Os -o $(HEX_FILE) $(INPUT_FILES) 

flash:
	$(AVR_FLASH) -c $(AVRDUDE_PROGRAMMER) -p $(AVRDUDE_DEVICE) $(HEX_FILE)

clean:
	rm *.o *.hex
