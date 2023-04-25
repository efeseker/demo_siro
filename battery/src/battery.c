#include <stdio.h>
#include <stdbool.h>

#define MAX_BATTERY_LEVEL 90
#define MIN_BATTERY_LEVEL 10
#define CHARGE_RATE 8
#define DISCHARGE_RATE 4
#define MAX_TEMPERATURE 45

int batteryLevel = 50;
bool isCharging = false;
float batteryTemperature = 25.0;

void checkBatteryStatus() {
    printf("Battery level: %d%%\n", batteryLevel);
    printf("Battery temperature: %.1f°C\n", batteryTemperature);
    if (batteryTemperature > MAX_TEMPERATURE) {
        printf("WARNING: Battery temperature is too high.\n");
    }
    if (batteryLevel >= 80) {
        printf("The battery is fully charged.\n");
    } else if (batteryLevel >= 50) {
        printf("The battery is partially charged.\n");
    } else if (batteryLevel >= 20) {
        printf("The battery is low.\n");
    } else {
        printf("The battery is critically low. Please charge immediately.\n");
    }
}

void chargeBattery() {
    isCharging = true;
    printf("Charging battery...\n");
    while (batteryLevel < MAX_BATTERY_LEVEL) {
        batteryLevel += CHARGE_RATE;
        if (batteryLevel > MAX_BATTERY_LEVEL) {
            batteryLevel = MAX_BATTERY_LEVEL;
        }
        batteryTemperature += 0.1 * CHARGE_RATE;
        if (batteryTemperature > MAX_TEMPERATURE) {
            printf("WARNING: Battery temperature is too high.\n");
        }
        checkBatteryStatus();
    }
    isCharging = false;
    printf("Battery fully charged.\n");
}

void dischargeBattery() {
    printf("Discharging battery...\n");
    while (batteryLevel > MIN_BATTERY_LEVEL) {
        batteryLevel -= DISCHARGE_RATE;
        if (batteryLevel < MIN_BATTERY_LEVEL) {
            batteryLevel = MIN_BATTERY_LEVEL;
        }
        batteryTemperature -= 0.1 * DISCHARGE_RATE;
        checkBatteryStatus();
    }
    printf("Battery fully discharged.\n");
}

int main() {
    char userAction;

    printf("Welcome to the battery management system.\n");
    checkBatteryStatus();

    while (true) {
        printf("Enter 'c' to charge the battery, 'd' to discharge the battery, or 'q' to quit: ");
        scanf(" %c", &userAction);
        switch (userAction) {
            case 'c':
                if (isCharging) {
                    printf("Battery is already charging.\n");
                } else {
                    chargeBattery();
                }
                break;
            case 'd':
                dischargeBattery();
                break;
            case 'q':
                printf("Goodbye.\n");
                return 0;
            default:
                printf("Invalid input. Please enter 'c', 'd', or 'q'.\n");
                break;
        }
    }

    return 0;
}
