CC = gcc
CFLAGS = -Wall

all: Yahboom-Rpi

Yahboom-Rpi: src/main.c
    $(CC) $(CFLAGS) -o $@ $^

clean:
    rm -f Yahboom-Rpi
