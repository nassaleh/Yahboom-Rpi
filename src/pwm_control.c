#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Function to write a value to a sysfs file
void writeSysfs(const char *path, const char *value) {
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        perror("Error opening sysfs file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s", value);

    fclose(file);
}

int TogglePWM() {
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

    // Export the PWM channel
    writeSysfs(export_path, "0");

    // Set the PWM period (e.g., 20ms -> 20000000 ns for servo motors)
    writeSysfs(period_path, "200000");

    // Enable the PWM output
    writeSysfs(enable_path, "1");
    

    // Set the PWM duty cycle (e.g., 1.5ms -> 1500000 ns to center a servo)
    writeSysfs(duty_cycle_path, "150000");
    sleep(1);
    writeSysfs(duty_cycle_path, "100000");
    sleep(1);
    writeSysfs(duty_cycle_path, "50000");
    sleep(1);
    writeSysfs(duty_cycle_path, "10000");
    sleep(1);
    writeSysfs(duty_cycle_path, "5000");
    sleep(1);
    writeSysfs(duty_cycle_path, "1000");
    sleep(1);



    // Sleep for 2 seconds
    sleep(2);

    // Disable the PWM output
    writeSysfs(enable_path, "0");

    // Unexport the PWM channel
    writeSysfs(export_path, "0");

    return 0;
}