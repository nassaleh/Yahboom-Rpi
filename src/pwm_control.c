#include "pwm_control.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <math.h>

static FILE *duty_cycle_file = NULL;

// TODO implement sig handler

// Function to write a value to a sysfs file
void writeSysfs(const char *path, const char *value)
{
    FILE *file = fopen(path, "w");
    if (file == NULL)
    {
        perror("Error opening sysfs file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s", value);

    fclose(file);
}

void AdjustBrightness(char* duty_cycle_value)
{
    int error = fprintf(duty_cycle_file, "%s", duty_cycle_value);
    fflush(duty_cycle_file);
    if(error < 0)
    {
        printf("Error writing to file\n");
    }
}

void InitDutyCycleFile(char *path)
{
    duty_cycle_file = fopen(path, "w");
    if (duty_cycle_file == NULL)
    {
        perror("Error opening sysfs file");
        exit(EXIT_FAILURE);
    }
}

int TogglePWM()
{
    // Define the PWM chip number and channel
    int pwm_chip = 0;
    int pwm_channel = 0;

    // Construct the sysfs file paths
    char export_path[64];
    char period_path[64];
    char duty_cycle_path[64];
    char enable_path[64];

    snprintf(export_path, sizeof(export_path), "/sys/class/pwm/pwmchip%d/export", pwm_chip);
    snprintf(period_path, sizeof(period_path), "/sys/class/pwm/pwmchip%d/pwm%d/period", pwm_chip, pwm_channel);
    snprintf(duty_cycle_path, sizeof(duty_cycle_path), "/sys/class/pwm/pwmchip%d/pwm%d/duty_cycle", pwm_chip, pwm_channel);
    snprintf(enable_path, sizeof(enable_path), "/sys/class/pwm/pwmchip%d/pwm%d/enable", pwm_chip, pwm_channel);

    InitDutyCycleFile(duty_cycle_path);

    // Export the PWM channel
    writeSysfs(export_path, "0");

    // Set the PWM period (e.g., 20ms -> 20000000 ns for servo motors)
    writeSysfs(period_path, "200000");

    // Enable the PWM output
    writeSysfs(enable_path, "1");

    pthread_t thread;

    int result = pthread_create(&thread, NULL, CycleLED, NULL);
    if (result != 0)
    {
        printf("Failed to create the thread.\n");
        return -1;
    }

    return 0;
    // Disable the PWM output
    writeSysfs(enable_path, "0");

    // Unexport the PWM channel
    writeSysfs(export_path, "0");

}

void* CycleLED(void* arg __attribute__((unused)))
{
    const double duration_seconds = 20.0;
    const double frequency_hz = 1.0;
    const int max_duty_cycle = 45000;

    // Calculate the number of iterations based on the desired duration
    const int num_iterations = (int)(duration_seconds * frequency_hz);
    for (int i = 0;; ++i)
    {
        // Calculate the duty cycle based on the sine function
        double sine_value = sin(2 * M_PI * frequency_hz * i / num_iterations);
        int duty_cycle_value = (int)((sine_value + 1.0) * 0.5 * max_duty_cycle);

        char duty_cycle[20];
        sprintf(duty_cycle, "%d", duty_cycle_value);
        AdjustBrightness(duty_cycle);
        usleep(50 * 1000);
    }

    // Max duty_cycle_path ~45k
}