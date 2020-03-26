cmake_minimum_required(VERSION 3.9)
project(RadioControlSoftware)

set(AVRSTRIP avr-strip)
set(OBJCOPY avr-objcopy)
set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)

set(CDEBUG "-gstabs")
set(CWARN "-Wall -Wextra -Wstrict-prototypes")
set(CTUNING "-funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums")
set(COPT "-Os")
set(CMCU "-mmcu=atmega328p")
set(CDEFS "-DF_CPU=16000000UL")
set(CFLAGS "${CMCU} ${CDEBUG} ${CDEFS} ${CINCS} ${COPT} ${CWARN} ${CEXTRA}")
set(CXXFLAGS "${CMCU} ${CDEFS} ${CINCS} ${COPT}")
set(CMAKE_C_FLAGS  ${CFLAGS})
set(CMAKE_CXX_FLAGS ${CXXFLAGS})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD  11)

set(SOURCES_HAL
        HAL/uart.c HAL/adc.c HAL/spi.c)
set(SOURCES_DRIVERS
        Drivers/ili9341.c Drivers/ili9341gfx.c Drivers/stmpe610.c Drivers/sx127x.c Drivers/rcLib/rc_lib.c)
SET(SOURCES_VIEW_ELEMENTS
        Util/View/Elements/button.c Util/View/Elements/label.c)
set(SOURCES_VIEW ${SOURCES_VIEW_ELEMENTS}
        Util/View/colors.c Util/View/ui.c Util/View/strings.c Util/View/colorconvert.c)
set(SOURCES_CONTROLLER_SCREENS
        Util/Controller/Screens/settings.c Util/Controller/Screens/start.c Util/Controller/Screens/flightmodes.c
        Util/Controller/Screens/calibrate.c Util/Controller/Screens/rfinfo.c Util/Controller/Screens/telemetry.c
        Util/Controller/Screens/debug.c)
set(SOURCES_CONTROLLER ${SOURCES_CONTROLLER_SCREENS}
        Util/Controller/controller.c Util/Controller/joystick.c)
set(SOURCES_MODEL
        Util/Model/model.c)
set(SOURCES_UTIL ${SOURCES_MODEL} ${SOURCES_CONTROLLER} ${SOURCES_VIEW})
set(SOURCES main.c ${SOURCES_HAL} ${SOURCES_DRIVERS} ${SOURCES_UTIL})

add_executable(${PROJECT_NAME} ${SOURCES})
add_compile_definitions("MAX_CHANNEL_COUNT=8")
add_compile_definitions("MAX_RESOLUTION=10")

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}.elf")

add_custom_target(strip ALL ${AVRSTRIP} "${PROJECT_NAME}.elf" DEPENDS ${PROJECT_NAME})
add_custom_target(${PROJECT_NAME}.hex   ALL ${OBJCOPY} -R .eeprom -O ihex "${PROJECT_NAME}.elf" "${PROJECT_NAME}.hex" DEPENDS strip)
