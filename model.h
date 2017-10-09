#ifndef _MODEL_H
#define _MODEL_H

namespace model{
    enum Flightmode{
        MANUAL = 0,
        LAUNCH = 1,
        LAND = 2,
        HOLD = 3,
        WAYPOINT = 4
    };
    
    Flightmode flightmode = LAUNCH;
    uint8_t armed = false;

    String getFlightMode(){
        switch(flightmode){
            case MANUAL:
                return "Manual";
            case LAUNCH:
                return "Launch";
            case LAND:
                return "Land";
            case HOLD:
                return "Hold";
            case WAYPOINT:
                return "Waypoint";
            default:
                return "";
        }
    }
}

#endif