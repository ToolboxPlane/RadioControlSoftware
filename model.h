#ifndef _MODEL_H
#define _MODEL_H

namespace model {
    enum Flightmode {
        MANUAL = 0,
        LAUNCH = 1,
        LAND = 2,
        HOLD = 3,
        WAYPOINT = 4
    };

    Flightmode flightmode = LAUNCH;
    uint8_t armed = false;
    String debugVals[6];
    uint8_t serialEnabled = false, loraEnabled = false;

    String getFlightMode(Flightmode mode = flightmode) {
        switch (mode) {
            case MANUAL:
                return F("Manual");
            case LAUNCH:
                return F("Launch");
            case LAND:
                return F("Land");
            case HOLD:
                return F("Hold");
            case WAYPOINT:
                return F("Waypoint");
            default:
                return "";
        }
    }
}

#endif