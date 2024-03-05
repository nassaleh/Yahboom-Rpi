#pragma once


#include <stdint.h>
#include <linux/i2c.h>

typedef struct
{
    int file;
} i2c_context;

int init_context(i2c_context *ctx, unsigned char i2c_bus, unsigned char i2c_address);
void swap_values(int *a, int *b);
int i2c_smbus_access(int fd, char rw, uint8_t command, int size, union i2c_smbus_data *data);
int wiringPiI2CWriteReg8(int fd, int reg, int value);

