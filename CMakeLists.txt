CMAKE_MINIMUM_REQUIRED(VERSION 3.8)
project(RadioControlSoftware)

SET(AVRSTRIP avr-strip)
SET(OBJCOPY avr-objcopy)

SET(CMAKE_C_COMPILER avr-gcc)
SET(CMAKE_CXX_COMPILER avr-g++)
SET(CDEBUG "-gstabs")
SET(CWARN "-Wall -Wstrict-prototypes")
SET(CTUNING "-funsigned-char -funsigned-bitfields -fpack-struct
-fshort-enums")
SET(COPT "-Os")
SET(CMCU "-mmcu=atmega328p")
SET(CDEFS "-DF_CPU=16000000UL")
SET(CFLAGS "${CMCU} ${CDEBUG} ${CDEFS} ${CINCS} ${COPT} ${CWARN} ${CEXTRA}")
SET(CXXFLAGS "${CMCU} ${CDEFS} ${CINCS} ${COPT}")
SET(CMAKE_C_FLAGS  ${CFLAGS})
SET(CMAKE_CXX_FLAGS ${CXXFLAGS})


SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_C_STANDARD  11)

ADD_EXECUTABLE(${PROJECT_NAME} main.cpp src/RadioControlProtocol/rcLib.cpp ili9341.c ili9341gfx.c label.cpp ui.h Joystick.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}.elf")

add_custom_target(strip ALL ${AVRSTRIP} "${PROJECT_NAME}.elf" DEPENDS ${PROJECT_NAME})
add_custom_target(${PROJECT_NAME}.hex   ALL ${OBJCOPY} -R .eeprom -O ihex "${PROJECT_NAME}.elf" "${PROJECT_NAME}.hex" DEPENDS strip)