cmake_minimum_required(VERSION 3.8)

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