#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <stdbool.h>
#include "rgb.c"

int initContext(rgb_context *rgb_ctx, unsigned char i2c_bus, unsigned char i2c_address);
void setFanSpeed(const rgb_context* ctx, const unsigned char speed);

int main()
{
    rgb_context ctx = {0};

    int i2c_bus = 1;
    int i2c_address = 0x0d;

    initContext(&ctx, i2c_bus, i2c_address);

    setFanSpeed(&ctx, 0x04);

    setRGBOff(&ctx);

    setRGBLightMode(&ctx, MODE_RAINBOW);

    setRGBLightBreathingColor(&ctx, BREATHING_BLUE);
    setRGBSpeed(&ctx, 0x01);
    setRGBSpeed(&ctx, 0x02);
    setRGBSpeed(&ctx, 0x03);

    setRGB(&ctx, RGB_1, 0xff, 0x00, 0x00);
    setRGB(&ctx, RGB_2, 0x00, 0xff, 0x00);
    setRGB(&ctx, RGB_3, 0x00, 0x00, 0xff);
}

int initContext(rgb_context *rgb_ctx, unsigned char i2c_bus, unsigned char i2c_address)
{
    char filename[20];
    snprintf(filename, 19, "/dev/i2c-%d", i2c_bus);

    int file = open(filename, O_RDWR);
    if (file < 0)
    {
        return -1;
    }

    if (ioctl(file, I2C_SLAVE, i2c_address) < 0)
    {
        return -2;
    }

    rgb_ctx->file = file;

    return 0;
}

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
