#include "rgb.h"
#include "fan.h"
#include "i2c_helper.h"
#include "ssd1306_i2c.h"
#include "pwm_control.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#include <math.h>
#include <signal.h>

void drawSineWave(void)
{
    int x, y;
    float A = 10.0;           // Amplitude
    float B = 2 * M_PI / 128; // Frequency factor based on screen width
    float C = 0;              // Phase shift
    float D = 16;             // Vertical shift to center the wave

    for (x = 0; x < 128; x++)
    {
        y = (int)(A * sin(B * (x + C)) + D);
        ssd1306_drawPixel(x, y, 1); // Assuming 1 is for drawing the pixel (color or on-state)
    }

    ssd1306_display();
    ssd1306_startscrollleft(0, 0x0f);
}

void printIpAddress(char *argv[])
{
    ssd1306_setTextSize(2);
    char *text = argv[1];
    ssd1306_drawString(text);
    ssd1306_display();
}

void toggleLed()
{
    for (int i = 0; i < 256; i++)
    {
        // setPWMValue(i);
        usleep(100);
        if (i == 255)
            i = 0;
    }
}

int main(int argc, char *argv[])
{
    signal(SIGINT, CloseDutyCycleFile);

    i2c_context ctx = {0};

    int i2c_bus = 1;
    int i2c_address = 0x0d;

    init_context(&ctx, i2c_bus, i2c_address);

    ssd1306_begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
    ssd1306_clearDisplay();

    TogglePWM();

    if (argc == 1)
    {
        drawSineWave();
    }
    else if (argc == 2)
    {
        printIpAddress(argv);
    }

    setFanSpeed(&ctx, 0x02);

    // setRGBOff(&ctx);

    setRGBLightMode(&ctx, MODE_RAINBOW);

    // setRGBLightBreathingColor(&ctx, BREATHING_BLUE);
    setRGBSpeed(&ctx, 0x01);
    // setRGBSpeed(&ctx, 0x02);
    // setRGBSpeed(&ctx, 0x03);

    pause();

    // setRGB(&ctx, RGB_1, 0xff, 0x00, 0x00);
    // setRGB(&ctx, RGB_2, 0x00, 0xff, 0x00);
    // setRGB(&ctx, RGB_3, 0x00, 0x00, 0xff);
}
