#pragma once

#include "rgb.h"

/// @brief Sets the fan speed according to the following:
/// 0x00 Off
/// 0x01 Max
/// 0x02 - 0x09 20% to 90% speed
/// @param speed A hex value indicating the speed
void setFanSpeed(const i2c_context* ctx, const unsigned char speed);