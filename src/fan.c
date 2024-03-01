#include "fan.h"
#include "rgb.h"

#include <unistd.h>
#include <stdio.h>

void setFanSpeed(const i2c_context* ctx, const unsigned char speed)
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