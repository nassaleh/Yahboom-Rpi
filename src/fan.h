#pragma once

#include <unistd.h>
#include <stdio.h>
#include "rgb.h"

/**
 * @brief Sets the fan speed according to the following:
 * 0x00 Off
 * 0x01 Max
 * 0x02 - 0x09 20% to 90% speed
 * @param speed A hex value indicating the speed
 */
void setFanSpeed(const rgb_context* ctx, const unsigned char speed)
{
    char buf[2] = {0x08, 0x00};

    buf[1] = speed > 0x09 ? 0x01 : speed;

    if (write(ctx->file, buf, 2) != 2)
    {
        /* ERROR HANDLING: i2c transaction failed */
        printf("Error");
    }
    printf("Set speed to: %x", buf[1]);
}
