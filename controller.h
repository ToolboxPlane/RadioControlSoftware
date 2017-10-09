#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "ui.h"
#include "model.h"

#define STMPE_CS 8

#define TS_MINX 150
#define TS_MINY 130
#define TS_MAXX 3800
#define TS_MAXY 4000

namespace controller{
    Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);

    enum Page{
        START,
        SETTINGS,
        CALIBRATE,
        FLIGHTMODES
    };

    Page page = START;
    

    void load(){
        ui::load();        
        ts.begin();        
    }

    int8_t getSelection(){
        static uint8_t eventHandled = false;
        if (ts.bufferEmpty()) {
            eventHandled = false;            
            for(uint8_t c=0; c<=5; c++){
                ui::buttonLabel[c].setColor(BUTTON_TEXT_COLOR);
            }
    
            return -1;
        }
        
        TS_Point p = ts.getPoint();
        
        p.x = map(p.x, TS_MINX, TS_MAXX, 0, 240);
        p.y = 320 - map(p.y, TS_MINY, TS_MAXY, 0, 320);

        if(p.y < 15){
            for(uint8_t c=0; c<=5; c++){
                ui::buttonLabel[c].setColor(BUTTON_TEXT_COLOR);
            }    

            return -1;
        }

        int8_t sel = (p.y-15)/50;

        for(uint8_t c=0; c<=5; c++){
            if(sel != c){
                ui::buttonLabel[c].setColor(BUTTON_TEXT_COLOR);
            } else {
                ui::buttonLabel[sel].setColor(BUTTON_TEXT_SELECTED_COLOR);
            }
        }

        if(!eventHandled){
            eventHandled = true;
            return sel;
        } else {
            return -1;
        }
    }

    void updateButtons(){
        switch(page){
            case START:
                ui::buttonLabel[0].setText("Arm/Disarm");
                ui::buttonLabel[1].setText("Flightmodes");
                ui::buttonLabel[2].setText("");
                ui::buttonLabel[3].setText("");
                ui::buttonLabel[4].setText("");
                ui::buttonLabel[5].setText("Calibrate");
                break;
            case CALIBRATE:
                ui::buttonLabel[0].setText("Move");
                ui::buttonLabel[1].setText("the");
                ui::buttonLabel[2].setText("Joysticks");
                ui::buttonLabel[3].setText("");
                ui::buttonLabel[4].setText("");
                ui::buttonLabel[5].setText("Finish");
                break;
            case FLIGHTMODES:
                ui::buttonLabel[0].setText("Manual");
                ui::buttonLabel[1].setText("Launch");
                ui::buttonLabel[2].setText("Land");
                ui::buttonLabel[3].setText("Hold");
                ui::buttonLabel[4].setText("Waypoint");
                ui::buttonLabel[5].setText("Back");
                break;
        }
    }

    void handleEvent(uint8_t sel){
        ui::update(model::armed, model::getFlightMode());
        
        switch(page){
            case START:
                switch (sel){
                    case 0:
                        model::armed = !model::armed;
                        break;
                    case 1:
                        page = FLIGHTMODES;
                        break;
                    case 5:
                        joyLeft.startCalibration();
                        joyRight.startCalibration();
                        page = CALIBRATE;
                        break;
                    default:
                        break;
                }
                break;
            case CALIBRATE:
                switch(sel){
                    case 5:
                        joyLeft.endCalibration(0);
                        joyRight.endCalibration(4);
                        page = START;
                        break;
                    default:
                        break;
                }
                break;
            case FLIGHTMODES:
                switch(sel){
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                        model::flightmode = sel;
                    case 5:
                        page = START;
                        break;
                }
                break;
            default:
                page = START;
                break;
        }
        updateButtons();
    }
}

#endif