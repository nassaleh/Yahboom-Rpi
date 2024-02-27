#include "rgb.h"

void setRGB(const rgb_context* ctx, unsigned char led, unsigned char red, unsigned char green, unsigned char blue)
{
    char MAX = 0x02;

    unsigned char buf[2] = {0x00, 0x00};
    buf[1] = led > MAX && led != 0xFF ? 0xFF : led;

    // Select LED
    if (write(ctx->file, buf, 2) != 2)
    {
        /* ERROR HANDLING: i2c transaction failed */
        printf("Error");
    }

    // Set Red Values
    buf[0] = 0x01;
    buf[1] = red;
    write(ctx->file, buf, 2);

    // Set Green Values
    buf[0] = 0x02;
    buf[1] = green;
    write(ctx->file, buf, 2);

    // Set Blue Values
    buf[0] = 0x03;
    buf[1] = blue;
    write(ctx->file, buf, 2);
}


void setRGBLightMode(const rgb_context* ctx, unsigned char mode)
{
    unsigned char MAX = 0x04;
    unsigned char buf[2] = {0x04, 0x00};

    buf[1] = mode > MAX ? 0x01 : mode;

    if (write(ctx->file, buf, 2) != 2)
    {
        /* ERROR HANDLING: i2c transaction failed */
        printf("Error");
    }
}

void setRGBSpeed(const rgb_context* ctx, unsigned char speed)
{
    unsigned char MAX = 0x03;
    unsigned char MIN = 0x01;

    unsigned char buf[2] = {0x05, 0x00};

    buf[1] = speed > MAX || speed < MIN ? 0x02 : speed;

    if (write(ctx->file, buf, 2) != 2)
    {
        /* ERROR HANDLING: i2c transaction failed */
        printf("Error");
    }
    printf("Set RGB speed to: %x", buf[1]);
}

/**
 * @brief Sets the light/breathing light color on an I2C-controlled device.
 *
 * This function takes a color code as a parameter and sends the corresponding I2C command
 * to set the light/breathing light color on the device. The color codes are as follows:
 * - 0x00: Red
 * - 0x01: Green (default)
 * - 0x02: Blue
 * - 0x03: Yellow
 * - 0x04: Purple
 * - 0x05: Cyan
 * - 0x06: White
 * If the provided color code is outside the valid range (greater than 0x06), it defaults
 * to green (0x01).
 *
 * The RGB mode must be set to 0x01 (Breathing) when calling \ref setRGBLightMode
 *
 * @param color The color code representing the desired light/breathing light color.
 *              Valid codes are 0x00 to 0x06.
 */
void setRGBLightBreathingColor(const rgb_context* ctx, unsigned char color)
{
    unsigned char MAX = 0x06;
    unsigned char buf[2] = {0x06, 0x00};

    buf[1] = color > MAX ? 0x01 : color;

    if (write(ctx->file, buf, 2) != 2)
    {
        /* ERROR HANDLING: i2c transaction failed */
        printf("Error");
    }
}

/**
 * @brief Turns off the RGB lights
 */
void setRGBOff(const rgb_context* ctx)
{
    unsigned char buf[2] = {0x07, 0x00};
    if (write(ctx->file, buf, 2) != 2)
    {
        /* ERROR HANDLING: i2c transaction failed */
        printf("Error");
    }
}