#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "../View/ui.h"
#include "../Model/model.h"
#include "../View/strings.h"

#define TS_MINX 150.0f
#define TS_MINY 130.0f
#define TS_MAXX 3800.0f
#define TS_MAXY 4000.0f

namespace controller {
    void updateButtons();

    enum Page {
        START,
        CALIBRATE,
        FLIGHTMODES,
        SETTINGS,
        DEBUG,
        LOG,
        DOWNLINK,
        RECEIVED_DATA
    };

    Page page = START;

    void load() {
        ui::load();
        stmpe610_init();
    }

    void setDebug(uint8_t index, uint16_t val) {
        if(index < 6) {
            model::debugVals[index] = val;
        }
    }

    int8_t getSelection() {
        static int8_t lastSel = -1;
        if (stmpe610_buffer_empty()) {
            ui::buttonLabel[lastSel].setColor(BUTTON_TEXT_COLOR);
            return lastSel =  -1;
        } else if(lastSel >= 0) {
            stmpe610_get_point();
            return -1;
        } else {
            tsPoint_t p = stmpe610_get_point();

            p.x = (uint16_t)((p.x - TS_MINX)/(TS_MAXX - TS_MINX) * 240);
            p.y = 320 - (uint16_t)((p.y - TS_MINY)/(TS_MAXY - TS_MINY) * 320);

            if (p.y < 15) {
                return -1;
            }

            lastSel = static_cast<int8_t>((p.y - 15) / 50);

            ui::buttonLabel[lastSel].setColor(BUTTON_TEXT_SELECTED_COLOR);
            return lastSel;
        }
    }

    void updateButtons() {
        switch (page) {
            case START:
                ui::buttonLabel[0].setText(TR(string_armDisarm));
                ui::buttonLabel[1].setText(TR(string_flightmodes));
                ui::buttonLabel[2].setText(TR(string_downlink));
                ui::buttonLabel[3].setText(TR(string_empty));
                ui::buttonLabel[4].setText(TR(string_settings));
                ui::buttonLabel[5].setText(TR(string_debug));
                break;
            case CALIBRATE:
                ui::buttonLabel[0].setText(TR(string_move));
                ui::buttonLabel[1].setText(TR(string_the));
                ui::buttonLabel[2].setText(TR(string_joysticks));
                ui::buttonLabel[3].setText(TR(string_empty));
                ui::buttonLabel[4].setText(TR(string_empty));
                ui::buttonLabel[5].setText(TR(string_finish));
                break;
            case SETTINGS:
                ui::buttonLabel[0].setText(TR(string_calibrate));
                if(model::serialEnabled()) {
                    ui::buttonLabel[1].setText(TR(string_disableUSB));
                } else {
                    ui::buttonLabel[1].setText(TR(string_enableUSB));
                }
                if(model::loraEnabled()) {
                    ui::buttonLabel[2].setText(TR(string_disableLora));
                } else {
                    ui::buttonLabel[2].setText(TR(string_enableLora));
                }
                ui::buttonLabel[3].setText(TR(string_empty));
                ui::buttonLabel[4].setText(TR(string_empty));
                ui::buttonLabel[5].setText(TR(string_back));
                break;
            case FLIGHTMODES:
                ui::buttonLabel[0].setText(TR(model::getFlightMode((model::Flightmode)0)));
                ui::buttonLabel[1].setText(TR(model::getFlightMode((model::Flightmode)1)));
                ui::buttonLabel[2].setText(TR(model::getFlightMode((model::Flightmode)2)));
                ui::buttonLabel[3].setText(TR(model::getFlightMode((model::Flightmode)3)));
                ui::buttonLabel[4].setText(TR(model::getFlightMode((model::Flightmode)4)));
                ui::buttonLabel[5].setText(TR(string_back));
                break;
            case DEBUG:
                ui::buttonLabel[0].setText(TR(string_log));
                ui::buttonLabel[1].setText(TR(string_version));
                ui::buttonLabel[2].setText(TR(string_compiledOn));
                ui::buttonLabel[3].setText(TR(string_compileDate));
                ui::buttonLabel[4].setText(TR(string_compileTime));
                ui::buttonLabel[5].setText(TR(string_back));
                break;
            case LOG:
                for(uint8_t c=0; c<6; c++) {
                    ui::buttonLabel[c].setNumber(model::debugVals[c]);
                }
                break;
            case DOWNLINK:
                ui::buttonLabel[0].setText(TR(string_snr));
                ui::buttonLabel[0].append(model::snr);
                ui::buttonLabel[1].setText(TR(string_rssi));
                ui::buttonLabel[1].append(model::rssi);
                ui::buttonLabel[2].setText(TR(string_sent));
                ui::buttonLabel[2].append(model::sent);
                ui::buttonLabel[3].setText(TR(string_received));
                ui::buttonLabel[3].append(model::received);
                ui::buttonLabel[4].setText(TR(string_empty));
                ui::buttonLabel[4].append(model::remoteRssi);
                ui::buttonLabel[5].setText(TR(string_back));
                break;
            case RECEIVED_DATA:
                ui::buttonLabel[0].setText(TR(string_empty));
                ui::buttonLabel[1].setText(TR(string_empty));
                ui::buttonLabel[2].setText(TR(string_empty));
                ui::buttonLabel[3].setText(TR(string_empty));
                ui::buttonLabel[4].setText(TR(string_empty));
                ui::buttonLabel[5].setText(TR(string_back));
                break;
        }
    }

    void handleEvent(int8_t sel) {
        ui::update(model::armed, model::getFlightMode());

        switch (page) {
            case START:
                switch (sel) {
                    case 0:
                        model::armed = static_cast<uint8_t>(!model::armed);
                        break;
                    case 1:
                        page = FLIGHTMODES;
                        break;
                    case 2:
                        page = DOWNLINK;
                        break;
                    case 3:
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
                        model::setSerialEnabled(!model::serialEnabled());
                        break;
                    case 2:
                        model::setLoraEnabled(!model::loraEnabled());
                        break;
                    case 5:
                        page = START;
                        break;
                }
                break;
            case DOWNLINK:
                if(sel == 4) {
                    page = RECEIVED_DATA;
                } else if(sel == 5) {
                    page = START;
                }
                break;
            case RECEIVED_DATA:
                if(sel == 5) {
                    page = DOWNLINK;
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
