#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#include "rgb.h"
#include "fan.h"
#include "i2c_helper.h"
#include "ssd1306_i2c.h"

int main()
{
    i2c_context ctx = {0};

    int i2c_bus = 1;
    int i2c_address = 0x0d;

    init_context(&ctx, i2c_bus, i2c_address);

    ssd1306_begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
    ssd1306_clearDisplay();
    char *text = "sysinfo-Error";
    ssd1306_drawString(text);
    ssd1306_display();

    setFanSpeed(&ctx, 0x02);

    // setRGBOff(&ctx);

    setRGBLightMode(&ctx, MODE_RAINBOW);

    // setRGBLightBreathingColor(&ctx, BREATHING_BLUE);
    setRGBSpeed(&ctx, 0x01);
    // setRGBSpeed(&ctx, 0x02);
    // setRGBSpeed(&ctx, 0x03);

    // setRGB(&ctx, RGB_1, 0xff, 0x00, 0x00);
    // setRGB(&ctx, RGB_2, 0x00, 0xff, 0x00);
    // setRGB(&ctx, RGB_3, 0x00, 0x00, 0xff);
}
