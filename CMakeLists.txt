cmake_minimum_required(VERSION 3.8)

project (DONT_USE_ME_IM_JUST_HERE_FOR_THE_DEPENDENCIES)

file(GLOB DONT_USE_ME_IM_JUST_HERE_FOR_THE_DEPENDENCIES_SRC
        "*.h"
        "*.cpp"
        "*.ino"
        )

add_executable(DONT_USE_ME_IM_JUST_HERE_FOR_THE_DEPENDENCIES ${DONT_USE_ME_IM_JUST_HERE_FOR_THE_DEPENDENCIES_SRC})

add_executable(EMPTY_RUN run.c)

add_custom_target(
        CompileArduino ALL
        COMMAND arduino --verify --board arduino:avr:uno main.inp
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
)

add_custom_target(
        FlashArduino ALL
        COMMAND arduino --upload --board arduino:avr:uno main.inp
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
)