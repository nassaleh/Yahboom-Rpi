#include "i2c_helper.h"
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <stdio.h>

int init_context(i2c_context *ctx, unsigned char i2c_bus, unsigned char i2c_address)
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

    ctx->file = file;

    return 0;
}

void swap_values(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int i2c_smbus_access(int fd, char rw, uint8_t command, int size, union i2c_smbus_data *data)
{
    struct i2c_smbus_ioctl_data args;

    args.read_write = rw;
    args.command = command;
    args.size = size;
    args.data = data;
    return ioctl(fd, I2C_SMBUS, &args);
}

int wiringPiI2CWriteReg8(int fd, int reg, int value)
{
    union i2c_smbus_data data;

    data.byte = value;
    return i2c_smbus_access(fd, I2C_SMBUS_WRITE, reg, I2C_SMBUS_BYTE_DATA, &data);
}