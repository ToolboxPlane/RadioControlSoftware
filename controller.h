#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "ui.h"
#include "model.h"
#include "strings.h"

#define TS_MINX 150.0f
#define TS_MINY 130.0f
#define TS_MAXX 3800.0f
#define TS_MAXY 4000.0f

namespace controller {
    void updateButtons();
    Joystick* joy;

    enum Page {
        START,
        CALIBRATE,
        FLIGHTMODES,
        SETTINGS,
        DEBUG,
        LOG,
        CHANNEL_MAPPING,
        CHANNEL_MAPPING_JOYSTICK_LEFT,
        CHANNEL_MAPPING_JOYSTICK_RIGHT,
        CHANNEL_MAPPING_FLIGHTMODES,
        CHANNEL_VALUES_0,
        CHANNEL_VALUES_1,
        DOWNLINK,
        RECEIVED_DATA
    };

    Page page = START;

    void load() {
        ui::load();
        model::loadChannelData();
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

            lastSel = (p.y - 15) / 50;

            ui::buttonLabel[lastSel].setColor(BUTTON_TEXT_SELECTED_COLOR);
            return lastSel;
        }
    }

    void updateButtons() {
        switch (page) {
            case START:
                ui::buttonLabel[0].setText(F(strings::armDisarm));
                ui::buttonLabel[1].setText(F(strings::flightmodes));
                ui::buttonLabel[2].setText(F(strings::downlink));
                ui::buttonLabel[3].setText(F(strings::channelMapping));
                ui::buttonLabel[4].setText(F(strings::settings));
                ui::buttonLabel[5].setText(F(strings::debug));
                break;
            case CALIBRATE:
                ui::buttonLabel[0].setText(F(strings::move));
                ui::buttonLabel[1].setText(F(strings::the));
                ui::buttonLabel[2].setText(F(strings::joysticks));
                ui::buttonLabel[3].setText(F(strings::empty));
                ui::buttonLabel[4].setText(F(strings::empty));
                ui::buttonLabel[5].setText(F(strings::finish));
                break;
            case SETTINGS:
                ui::buttonLabel[0].setText(F(strings::calibrate));
                if(model::serialEnabled()) {
                    ui::buttonLabel[1].setText(F(strings::disableUSB));
                } else {
                    ui::buttonLabel[1].setText(F(strings::enableUSB));
                }
                if(model::loraEnabled()) {
                    ui::buttonLabel[2].setText(F(strings::disableLora));
                } else {
                    ui::buttonLabel[2].setText(F(strings::enableLora));
                }
                ui::buttonLabel[3].setText(F(strings::empty));
                ui::buttonLabel[4].setText(F(strings::empty));
                ui::buttonLabel[5].setText(F(strings::back));
                break;
            case FLIGHTMODES:
                ui::buttonLabel[0].setText(F(model::getFlightMode((model::Flightmode)0)));
                ui::buttonLabel[1].setText(F(model::getFlightMode((model::Flightmode)1)));
                ui::buttonLabel[2].setText(F(model::getFlightMode((model::Flightmode)2)));
                ui::buttonLabel[3].setText(F(model::getFlightMode((model::Flightmode)3)));
                ui::buttonLabel[4].setText(F(model::getFlightMode((model::Flightmode)4)));
                ui::buttonLabel[5].setText(F(strings::back));
                break;
            case DEBUG:
                ui::buttonLabel[0].setText(F(strings::log));
                ui::buttonLabel[1].setText(F(strings::version));
                ui::buttonLabel[2].setText(F(strings::compiledOn));
                ui::buttonLabel[3].setText(F(strings::compileDate));
                ui::buttonLabel[4].setText(F(strings::compileTime));
                ui::buttonLabel[5].setText(F(strings::back));
                break;
            case CHANNEL_MAPPING:
                ui::buttonLabel[0].setText(F(strings::leftJoy));
                ui::buttonLabel[1].setText(F(strings::rightJoy));
                ui::buttonLabel[2].setText(F(strings::flightmodes));
                ui::buttonLabel[3].setText(F(strings::empty));
                ui::buttonLabel[4].setText(F(strings::empty));
                ui::buttonLabel[5].setText(F(strings::back));
                break;
            case CHANNEL_MAPPING_JOYSTICK_LEFT:
                ui::buttonLabel[0].setText(F(strings::xAxis));
                ui::buttonLabel[0].append(joyLeft.getXChannel());
                ui::buttonLabel[0].append(")", 1);
                ui::buttonLabel[1].setText(F(strings::yAxis));
                ui::buttonLabel[1].append(joyLeft.getYChannel());
                ui::buttonLabel[1].append(")", 1);
                ui::buttonLabel[2].setText(F(strings::button));
                ui::buttonLabel[2].append(joyLeft.getBtnChannel());
                ui::buttonLabel[2].append(")", 1);
                ui::buttonLabel[3].setText(F(strings::empty));
                ui::buttonLabel[4].setText(F(strings::empty));
                ui::buttonLabel[5].setText(F(strings::back));
                break;
            case CHANNEL_MAPPING_JOYSTICK_RIGHT:
                ui::buttonLabel[0].setText(F(strings::xAxis));
                ui::buttonLabel[0].append(joyRight.getXChannel());
                ui::buttonLabel[0].append(")", 1);
                ui::buttonLabel[1].setText(F(strings::yAxis));
                ui::buttonLabel[1].append(joyRight.getYChannel());
                ui::buttonLabel[1].append(")", 1);
                ui::buttonLabel[2].setText(F(strings::button));
                ui::buttonLabel[2].append(joyRight.getBtnChannel());
                ui::buttonLabel[2].append(")", 1);
                ui::buttonLabel[3].setText(F(strings::empty));
                ui::buttonLabel[4].setText(F(strings::empty));
                ui::buttonLabel[5].setText(F(strings::back));
                break;
            case CHANNEL_MAPPING_FLIGHTMODES:
                ui::buttonLabel[0].setText(F(strings::fmode));
                ui::buttonLabel[0].append(model::flightmodeChannel);
                ui::buttonLabel[0].append(")", 1);
                ui::buttonLabel[1].setText(F(strings::armed));
                ui::buttonLabel[1].append(model::armedChannnel);
                ui::buttonLabel[1].append(")", 1);
                ui::buttonLabel[2].setText(F(strings::empty));
                ui::buttonLabel[3].setText(F(strings::empty));
                ui::buttonLabel[4].setText(F(strings::empty));
                ui::buttonLabel[5].setText(F(strings::back));
                break;
            case CHANNEL_VALUES_0:
                ui::buttonLabel[0].setNumber(0);
                ui::buttonLabel[1].setNumber(1);
                ui::buttonLabel[2].setNumber(2);
                ui::buttonLabel[3].setNumber(3);
                ui::buttonLabel[4].setText(F(strings::next));
                ui::buttonLabel[5].setText(F(strings::back));
                break;
            case CHANNEL_VALUES_1:
                ui::buttonLabel[0].setNumber(4);
                ui::buttonLabel[1].setNumber(5);
                ui::buttonLabel[2].setNumber(6);
                ui::buttonLabel[3].setNumber(7);
                ui::buttonLabel[4].setText(F(strings::previous));
                ui::buttonLabel[5].setText(F(strings::back));
                break;
            case LOG: 
                for(uint8_t c=0; c<6; c++) {
                    ui::buttonLabel[c].setNumber(model::debugVals[c]);
                }
                break;
            case DOWNLINK:
                ui::buttonLabel[0].setText(F(strings::snr));
                ui::buttonLabel[1].setText(F(strings::rssi));
                ui::buttonLabel[2].setText(F(strings::received));
                ui::buttonLabel[3].setText(F(strings::sent));
                ui::buttonLabel[4].setText(F(strings::receivedData));
                ui::buttonLabel[5].setText(F(strings::back));
                break;
            case RECEIVED_DATA:
                ui::buttonLabel[0].setText(F(strings::empty));
                ui::buttonLabel[1].setText(F(strings::empty));
                ui::buttonLabel[2].setText(F(strings::empty));
                ui::buttonLabel[3].setText(F(strings::empty));
                ui::buttonLabel[4].setText(F(strings::empty));
                ui::buttonLabel[5].setText(F(strings::back));
                break;
        }
    }

    void handleEvent(int8_t sel) {
        static uint8_t type;

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
                    case 2:
                        page = DOWNLINK;
                        break;
                    case 3:
                        page = CHANNEL_MAPPING;
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
            case CHANNEL_MAPPING:
                switch (sel) {
                    case 0:
                        page = CHANNEL_MAPPING_JOYSTICK_LEFT;
                        joy = &joyLeft;
                        type = 0;
                        break;
                    case 1:
                        page = CHANNEL_MAPPING_JOYSTICK_RIGHT;
                        joy = &joyRight;
                        type = 5;
                        break;
                    case 2:
                        page = CHANNEL_MAPPING_FLIGHTMODES;
                        type = 10;
                        break;
                    case 5:
                        page = START;
                        break;
                }
                break;
            case CHANNEL_MAPPING_JOYSTICK_LEFT:
            case CHANNEL_MAPPING_JOYSTICK_RIGHT:
            case CHANNEL_MAPPING_FLIGHTMODES:
                switch(sel) {
                    case 0:
                    case 1:
                    case 2:
                        type += sel;
                        page = CHANNEL_VALUES_0;
                        break;
                    case 5:
                        page = CHANNEL_MAPPING;
                }
                break;
            case CHANNEL_VALUES_0:
                switch (sel) {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                        model::mapToChannel(type, sel);
                        page = CHANNEL_MAPPING;
                        break;
                    case 4:
                        page = CHANNEL_VALUES_1;
                        break;
                    case 5:
                        page = CHANNEL_MAPPING;
                        break;                        
                }
                break;
            case CHANNEL_VALUES_1:
                switch (sel) {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                        model::mapToChannel(type, sel+4);
                        page = CHANNEL_MAPPING;
                        break;
                    case 4:
                        page = CHANNEL_VALUES_0;
                        break;
                    case 5:
                        page = CHANNEL_MAPPING;
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
