#include "uiMacros.hpp"

#define HOME 0
#define JOYSTICK_CALIBRATE 1
#define FLIGHTMODE 2
#define ABOUT 3

addButton(HOME, 0,"Arm/Disarm")
addButtonR(HOME, 1,"Flightmodes",FLIGHTMODE)
addButtonR(HOME, 4, "Calibrate",JOYSTICK_CALIBRATE)
addButtonR(HOME, 5, "About", ABOUT)

addButton(JOYSTICK_CALIBRATE, 0, "Move")
addButton(JOYSTICK_CALIBRATE, 1, "the")
addButton(JOYSTICK_CALIBRATE, 2, "Buttons")
addButtonR(JOYSTICK_CALIBRATE, 5, "Back", HOME)

addButton(FLIGHTMODE, 0, "Manual")
addButton(FLIGHTMODE, 1, "Launch")
addButton(FLIGHTMODE, 2, "Land")
addButton(FLIGHTMODE, 3, "Hold")
addButton(FLIGHTMODE, 4, "Waypoint")
addButtonR(FLIGHTMODE, 5, "Back", HOME)

addButton(ABOUT, 0, "Buildtime:")
addButton(ABOUT, 1, __TIMESTAMP__)
addButtonR(ABOUT, 5, "Back", HOME)

callbacks(HOME)
    onPress(0,model::armed = !model::armed;)
    onPress(4,
        joyLeft.startCalibration();
        joyRight.startCalibration();
    )
endCallbacks

callbacks(JOYSTICK_CALIBRATE)
    onPress(5,
        joyLeft.endCalibration(0);
        joyRight.endCalibration(4);
    )
endCallbacks

callbacks(FLIGHTMODE)
    onPress(0,model::flightmode = (model::Flightmode) 0;)
    onPress(1,model::flightmode = (model::Flightmode) 1;)
    onPress(2,model::flightmode = (model::Flightmode) 2;)
    onPress(3,model::flightmode = (model::Flightmode) 3;)
    onPress(4,model::flightmode = (model::Flightmode) 4;)
endCallbacks