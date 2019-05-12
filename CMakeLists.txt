cmake_minimum_required(VERSION 3.8)
project(RadioControlSoftware)

set(AVRSTRIP avr-strip)
set(OBJCOPY avr-objcopy)

set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)
set(CDEBUG "-gstabs")
set(CWARN "-Wall -Wstrict-prototypes")
set(CTUNING "-funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums")
set(COPT "-Os")
set(CMCU "-mmcu=atmega328p")
set(CDEFS "-DF_CPU=16000000UL")
set(CFLAGS "${CMCU} ${CDEBUG} ${CDEFS} ${CINCS} ${COPT} ${CWARN} ${CEXTRA}")
set(CXXFLAGS "${CMCU} ${CDEFS} ${CINCS} ${COPT}")
set(CMAKE_C_FLAGS  ${CFLAGS})
set(CMAKE_CXX_FLAGS ${CXXFLAGS})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD  11)

set(SOURCES_HAL HAL/uart.c HAL/adc.c)
set(SOURCES_DRIVERS Drivers/ili9341.c Drivers/ili9341gfx.c Drivers/LoRa.cpp Drivers/stmpe610.c Drivers/rcLib/rc_lib.c)
set(SOURCES main.cpp Util/View/label.c Util/Controller/joystick.c Util/View/colorconvert.c
        Util/View/strings.c Util/View/ui.c Util/Model/model.c Util/Controller/controller.c)

ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCES_HAL} ${SOURCES_DRIVERS} ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}.elf")

add_custom_target(strip ALL ${AVRSTRIP} "${PROJECT_NAME}.elf" DEPENDS ${PROJECT_NAME})
add_custom_target(${PROJECT_NAME}.hex   ALL ${OBJCOPY} -R .eeprom -O ihex "${PROJECT_NAME}.elf" "${PROJECT_NAME}.hex" DEPENDS strip)