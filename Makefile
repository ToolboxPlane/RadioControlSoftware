all: flash

build:
    arduino --verify --board arduino\:avr\:uno main.ino

flash:
    arduino --upload --board arduino\:avr\:uno main.ino
