/* Stepper basic example.
 *
 * Connect a 4-wire stepper motor a motor driver, then this to the
 * Pico. The motor will variously rotate and pause as noted below.
 * 
 * 
 * Copyright (c) 2021 Antonio González
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "stepper.h"

// Stepper constants.
stepper_t stepper;
const uint8_t stepper_pin_1A = 12;
const uint8_t stepper_pin_1B = 13;
const uint8_t stepper_pin_2A = 14;
const uint8_t stepper_pin_2B = 15;
const uint16_t stepper_steps_per_revolution = 200;
const stepper_mode_t stepping_mode = single;
uint8_t speed = 20;

int main() {
    stdio_init_all();

    // Initialise the stepper
    stepper_init(&stepper, stepper_pin_1A, stepper_pin_1B,
                 stepper_pin_2A, stepper_pin_2B,
                 stepper_steps_per_revolution, stepping_mode);
    stepper_set_speed_rpm(&stepper, speed);

    while (true) {
        // Rotate 3/4 of a turn.
        stepper_rotate_degrees(&stepper, 270);
        sleep_ms(500);

        // Now rotate these many steps in the oposite direction
        stepper_rotate_steps(&stepper, -45);
        sleep_ms(500);

        // Increase the speed and rotate 360 degrees
        speed = 50;
        stepper_set_speed_rpm(&stepper, speed);
        stepper_rotate_degrees(&stepper, 360);

        // Release the coils and sleep for a while. You can check that
        // the coils are not energised by moving the rotor manually:
        // there should be little resistance.
        stepper_release(&stepper);
        sleep_ms(4000);

        // Decrease the speed
        speed = 15;
        stepper_set_speed_rpm(&stepper, speed);
    }
    return 0;
}

