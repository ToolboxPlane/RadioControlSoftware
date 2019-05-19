/**
 * @file colors.c
 * @author paul
 * @date 19.05.19
 * @brief colors @TODO
 */

#include <stdint.h>
#include "colors.h"
#include "colorconvert.h"
#include "materialcolors.h"

// See: https://material.io/tools/color/#!/?view.left=0&view.right=0&primary.color=2196F3
const uint16_t BACKGROUND_COLOR = R8G8B8_TO_R5G6B5(GREY_P200);
const uint16_t NOTIF_COLOR = R8G8B8_TO_R5G6B5(0x0069C0);
const uint16_t BUTTON_COLOR = R8G8B8_TO_R5G6B5(0x2196f3);
const uint16_t NOTIF_TEXT_COLOR = R8G8B8_TO_R5G6B5(WHITE);
const uint16_t BUTTON_TEXT_COLOR = R8G8B8_TO_R5G6B5(WHITE);
