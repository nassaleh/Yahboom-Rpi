#pragma once
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <stdio.h>

typedef struct
{
    int file;
} i2c_context;

int initContext(i2c_context *ctx, unsigned char i2c_bus, unsigned char i2c_address)
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

void swap_values(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
