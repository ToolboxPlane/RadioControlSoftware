/**
 * @file colors.c
 * @author paul
 * @date 19.05.19
 * @brief colors @TODO
 */

#include <stdint.h>
#include "colors.h"
#include "colorconvert.h"
#include "materialColors.h"

const uint16_t BACKGROUND_COLOR = R8G8B8TOR5G6B5(GREY_P200);
const uint16_t NOTIF_COLOR = R8G8B8TOR5G6B5(0x0069C0);
const uint16_t BUTTON_COLOR = R8G8B8TOR5G6B5(0x2196f3);
const uint16_t NOTIF_TEXT_COLOR = R8G8B8TOR5G6B5(WHITE);
const uint16_t BUTTON_TEXT_COLOR = R8G8B8TOR5G6B5(WHITE);
