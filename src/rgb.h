#ifndef YAHBOOM_RGB_H
#define YAHBOOM_RGB_H

enum RGBControl
{
    RGB_1 = 0x00,  /**< Control RGB Light 1 */
    RGB_2 = 0x01,  /**< Control RGB Light 2 */
    RGB_3 = 0x02,  /**< Control RGB Light 3 */
    RGB_ALL = 0xFF /**< Control All RGB Lights */
};

enum RGBLightMode
{
    MODE_WATER = 0x00,     /**< Water Light Mode */
    MODE_BREATHING = 0x01, /**< Breathing Light Mode */
    MODE_MARQUEE = 0x02,   /**< Marquee Mode */
    MODE_RAINBOW = 0x03,   /**< Rainbow Light Mode */
    MODE_COLORFUL = 0x04   /**< Colorful Light Mode */
};

enum BreathingLightColor
{
    BREATHING_RED = 0x00,    /**< Breathing Light Red Color */
    BREATHING_GREEN = 0x01,  /**< Breathing Light Green Color (Default) */
    BREATHING_BLUE = 0x02,   /**< Breathing Light Blue Color */
    BREATHING_YELLOW = 0x03, /**< Breathing Light Yellow Color */
    BREATHING_PURPLE = 0x04, /**< Breathing Light Purple Color */
    BREATHING_CYAN = 0x05,   /**< Breathing Light Cyan Color */
    BREATHING_WHITE = 0x06   /**< Breathing Light White Color */
};

typedef struct
{
    int file;
} rgb_context;

/**
 * @brief Sets the RGB values for an LED on an I2C-controlled device.
 * @param led The index of the LED (0 to 2) to set the color for. Use 0xFF to set all LEDs.
 * @param red The red component of the RGB color (0 to 255).
 * @param green The green component of the RGB color (0 to 255).
 * @param blue The blue component of the RGB color (0 to 255).
 */
void setRGB(const rgb_context* ctx, unsigned char led, unsigned char red, unsigned char green, unsigned char blue);


/**
 * @brief Sets the RGB mode according to the following:
 * 0x00 water light
 * 0x01 Breathing
 * 0x02 Marquee
 * 0x03 Rainbow light
 * 0x04 Colorful light
 * @param mode A hex value indicating the speed \ref
 */
void setRGBLightMode(const rgb_context* ctx, unsigned char mode);


/**
 * @brief Sets the Speed of RGB switch:
 * 0x01 slow speed，0x02 middle speed(default),0x03 fast speed
 * @param Speed of rgb switching
 */
void setRGBSpeed(const rgb_context* ctx, unsigned char speed);


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
void setRGBLightBreathingColor(const rgb_context* ctx, unsigned char color);


/**
 * @brief Turns off the RGB lights
 */
void setRGBOff(const rgb_context* ctx);

#endif // YAHBOOM_RGB_H