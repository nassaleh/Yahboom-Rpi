#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>

#define i2c_bus 1
#define i2c_address 0x0d

enum RGBControl {
    RGB_1 = 0x00, /**< Control RGB Light 1 */
    RGB_2 = 0x01, /**< Control RGB Light 2 */
    RGB_3 = 0x02, /**< Control RGB Light 3 */
    RGB_ALL = 0xFF /**< Control All RGB Lights */
};

enum RGBLightMode {
    MODE_WATER = 0x00,     /**< Water Light Mode */
    MODE_BREATHING = 0x01, /**< Breathing Light Mode */
    MODE_MARQUEE = 0x02,   /**< Marquee Mode */
    MODE_RAINBOW = 0x03,   /**< Rainbow Light Mode */
    MODE_COLORFUL = 0x04   /**< Colorful Light Mode */
};

enum BreathingLightColor {
    BREATHING_RED = 0x00,     /**< Breathing Light Red Color */
    BREATHING_GREEN = 0x01,   /**< Breathing Light Green Color (Default) */
    BREATHING_BLUE = 0x02,    /**< Breathing Light Blue Color */
    BREATHING_YELLOW = 0x03,  /**< Breathing Light Yellow Color */
    BREATHING_PURPLE = 0x04,  /**< Breathing Light Purple Color */
    BREATHING_CYAN = 0x05,    /**< Breathing Light Cyan Color */
    BREATHING_WHITE = 0x06    /**< Breathing Light White Color */
};

int file;

int main()
{
    char filename[20];
    snprintf(filename, 19, "/dev/i2c-%d", i2c_bus);
    file = open(filename, O_RDWR);
    if (file < 0)
    {
        exit(1);
    }

    if (ioctl(file, I2C_SLAVE, i2c_address) < 0)
    {
        exit(1);
    }

    setFanSpeed(0x04);

    setRGBLightMode(RAINBOW);

    setRGBLightBreathingColor(BREATHING_BLUE);
    setRGBSpeed(0x01);
    setRGBSpeed(0x02);
    setRGBSpeed(0x03);

    setRGB(led1, 0xff, 0x00, 0x00);
    setRGB(led2, 0x00, 0xff, 0x00);
    setRGB(led3, 0x00, 0x00, 0xff);
}

/**
 * @brief Sets the RGB values for an LED on an I2C-controlled device.
 * @param led The index of the LED (0 to 2) to set the color for. Use 0xFF to set all LEDs.
 * @param red The red component of the RGB color (0 to 255).
 * @param green The green component of the RGB color (0 to 255).
 * @param blue The blue component of the RGB color (0 to 255).
 */
void setRGB(unsigned char led, unsigned char red, unsigned char green, unsigned char blue)
{
    char MAX = 0x02;

    unsigned char buf[2] = {0x00, 0x00};
    buf[1] = led > MAX && led != 0xFF ? 0xFF : led;

    // Select LED
    if (write(file, buf, 2) != 2)
    {
        /* ERROR HANDLING: i2c transaction failed */
        printf("Error");
    }

    // Set Red Values
    buf[0] = 0x01;
    buf[1] = red;
    write(file, buf, 2);

    // Set Green Values
    buf[0] = 0x02;
    buf[1] = green;
    write(file, buf, 2);

    // Set Blue Values
    buf[0] = 0x03;
    buf[1] = blue;
    write(file, buf, 2);
}

/**
 * @brief Sets the RGB mode according to the following:
 * 0x00 water light
 * 0x01 Breathing
 * 0x02 Marquee
 * 0x03 Rainbow light
 * 0x04 Colorful light
 * @param speed A hex value indicating the speed
 */
void setRGBLightMode(char mode)
{
    unsigned char MAX = 0x04;
    unsigned char buf[2] = {0x04, 0x00};

    buf[1] = mode > MAX ? 0x01 : mode;

    if (write(file, buf, 2) != 2)
    {
        /* ERROR HANDLING: i2c transaction failed */
        printf("Error");
    }
}

/**
 * @brief Sets the Speed of RGB switch:
 * 0x01 slow speed，0x02 middle speed(default),0x03 fast speed
 * @param Speed of rgb switching
 */
void setRGBSpeed(unsigned char speed)
{
    unsigned char MAX = 0x03;
    unsigned char MIN = 0x01;

    unsigned char buf[2] = {0x05, 0x00};

    buf[1] = speed > MAX || speed < MIN ? 0x02 : speed;

    if (write(file, buf, 2) != 2)
    {
        /* ERROR HANDLING: i2c transaction failed */
        printf("Error");
    }
    printf("Set speed to: %x", buf[1]);
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
void setRGBLightBreathingColor(unsigned char color)
{
    unsigned char MAX = 0x06;
    unsigned char buf[2] = {0x06, 0x00};

    buf[1] = color > MAX ? 0x01 : color;

    if (write(file, buf, 2) != 2)
    {
        /* ERROR HANDLING: i2c transaction failed */
        printf("Error");
    }
}

/**
 * @brief Sets the fan speed according to the following:
 * 0x00 Off
 * 0x01 Max
 * 0x02 - 0x09 20% to 90% speed
 * @param speed A hex value indicating the speed
 */
void setFanSpeed(char speed)
{
    char buf[2] = {0x08, 0x00};

    buf[1] = speed > 0x09 ? 0x01 : speed;

    if (write(file, buf, 2) != 2)
    {
        /* ERROR HANDLING: i2c transaction failed */
        printf("Error");
    }
    printf("Set speed to: %x", buf[1]);
}