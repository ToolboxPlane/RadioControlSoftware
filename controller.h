#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "ui.h"
#include "model.h"

#define STMPE_CS 8

#define TS_MINX 150
#define TS_MINY 130
#define TS_MAXX 3800
#define TS_MAXY 4000

namespace controller {
    Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);
    void updateButtons();

    enum Page {
        START,
        CALIBRATE,
        FLIGHTMODES,
        SETTINGS,
        DEBUG,
        LOG
    };

    Page page = START;

    void load() {
        ui::load();
        ts.begin();
    }

    void setDebug(uint8_t index, String val) {
        if(index >= 0 && index < 6) {
            model::debugVals[index] = val;
        }
    }

    void setDebug(uint8_t index, int val) {
        return setDebug(index, String(val));
    }

    int8_t getSelection() {
        static int8_t lastSel = -1;
        if (ts.bufferEmpty()) {
            ui::buttonLabel[lastSel].setColor(BUTTON_TEXT_COLOR);
            return lastSel =  -1;
        } else if(lastSel >= 0) {
            ts.getPoint();
            return -1;
        } else {
            TS_Point p = ts.getPoint();

            p.x = map(p.x, TS_MINX, TS_MAXX, 0, 240);
            p.y = 320 - map(p.y, TS_MINY, TS_MAXY, 0, 320);

            if (p.y < 15) {
                return -1;
            }

            lastSel = (p.y - 15) / 50;

            ui::buttonLabel[lastSel].setColor(BUTTON_TEXT_SELECTED_COLOR);
            return lastSel;
        }
    }

    void updateButtons() {
        switch (page) {
            case START:
                ui::buttonLabel[0].setText(F("Arm/Disarm"));
                ui::buttonLabel[1].setText(F("Flightmodes"));
                ui::buttonLabel[2].setText("");
                ui::buttonLabel[3].setText("");
                ui::buttonLabel[4].setText(F("Settings"));
                ui::buttonLabel[5].setText(F("Debug"));
                break;
            case CALIBRATE:
                ui::buttonLabel[0].setText(F("Move"));
                ui::buttonLabel[1].setText(F("the"));
                ui::buttonLabel[2].setText(F("Joysticks"));
                ui::buttonLabel[3].setText("");
                ui::buttonLabel[4].setText("");
                ui::buttonLabel[5].setText(F("Finish"));
                break;
            case SETTINGS:
                ui::buttonLabel[0].setText(F("Calibrate"));
                if(model::serialEnabled) {
                    ui::buttonLabel[1].setText(F("Disable USB"));
                } else {
                    ui::buttonLabel[1].setText(F("Enable USB"));
                }
                if(model::loraEnabled) {
                    ui::buttonLabel[2].setText(F("Disable LoRa"));
                } else {
                    ui::buttonLabel[2].setText(F("Enable LoRa"));
                }
                ui::buttonLabel[3].setText("");
                ui::buttonLabel[4].setText("");
                ui::buttonLabel[5].setText(F("Back"));
                break;
            case FLIGHTMODES:
                ui::buttonLabel[0].setText(model::getFlightMode(0));
                ui::buttonLabel[1].setText(model::getFlightMode(1));
                ui::buttonLabel[2].setText(model::getFlightMode(2));
                ui::buttonLabel[3].setText(model::getFlightMode(3));
                ui::buttonLabel[4].setText(model::getFlightMode(4));
                ui::buttonLabel[5].setText(F("Back"));
                break;
            case DEBUG:
                ui::buttonLabel[0].setText(F("Log"));
                ui::buttonLabel[1].setText("");
                ui::buttonLabel[2].setText(F("Compiled on:"));
                ui::buttonLabel[3].setText(F(__TIME__));
                ui::buttonLabel[4].setText(F(__DATE__));
                ui::buttonLabel[5].setText(F("Back"));
                break;
            case LOG: 
                for(uint8_t c=0; c<6; c++) {
                    ui::buttonLabel[c].setText(model::debugVals[c]);
                }
                break;
        }
    }

    void handleEvent(uint8_t sel) {
        ui::update(model::armed, model::getFlightMode());

        switch (page) {
            case START:
                switch (sel) {
                    case 0:
                        model::armed = !model::armed;
                        break;
                    case 1:
                        page = FLIGHTMODES;
                        break;
                    case 4:
                        page = SETTINGS;
                        break;
                    case 5:
                        page = DEBUG;
                        break;
                    default:
                        break;
                }
                break;
            case CALIBRATE:
                switch (sel) {
                    case 5:
                        joyLeft.endCalibration(0);
                        joyRight.endCalibration(4);
                        page = SETTINGS;
                        break;
                    default:
                        break;
                }
                break;
            case FLIGHTMODES:
                switch (sel) {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                        model::flightmode = (model::Flightmode) sel;
                    case 5:
                        page = START;
                        break;
                }
                break;
            case SETTINGS:
                switch (sel) {
                    case 0:
                        joyLeft.startCalibration();
                        joyRight.startCalibration();
                        page = CALIBRATE;
                        break;
                    case 1:
                        model::serialEnabled = !model::serialEnabled;
                        break;
                    case 2:
                        model::loraEnabled = !model::loraEnabled;
                        break;
                    case 5:
                        page = START;
                        break;
                }
                break;
            case DEBUG:
                switch (sel) {
                    case 0:
                        page = LOG;
                        break;
                    case 5:
                        page = START;
                        break;
                }
                break;
            case LOG:
                switch (sel) {
                    case 5:
                        page = DEBUG;
                        break;
                }
                break;
            default:
                page = START;
                break;
        }
        controller::updateButtons();
    }
}

#endif
