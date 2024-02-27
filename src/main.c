#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
// #include <i2c/smbus.h>

#define i2c_bus 1
#define i2c_address 0x0d

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

    setFanSpeed(0x01);
    setRGBMode(0x03);
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

    sleep(1);
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
void setRGBMode(char mode)
{
    char MAX = 0x04;
    char buf[2] = {0x04, 0x00};

    buf[1] = mode > MAX ? 0x01 : mode;

    if (write(file, buf, 2) != 2)
    {
        /* ERROR HANDLING: i2c transaction failed */
        printf("Error");
    }
    printf("Set speed to: %x", buf[1]);

    sleep(1);
}
