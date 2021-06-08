/*
 * Copyright (c) 2021 Antonio González
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 */

#ifndef _STEPPER_H_
#define _STEPPER_H_

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

typedef struct {
    int16_t position;
    uint64_t now;
    uint64_t last_step_us_time;
    uint64_t step_delay_us;
    uint32_t gpio_mask;
    uint32_t stepping_sequence[4];
    float step_angle;
    uint16_t steps_per_revolution;
} stepper_t;

typedef enum {
    single,
    power
} stepper_mode_t;


/*! \brief Initialise a stepper motor
 *
 *  \param s Pointer to a stepper_t structure
 *  \param pin_1A GPIO to control coil A, first coil pair
 *  \param pin_1B GPIO to control coil B, first coil pair
 *  \param pin_2A GPIO to control coil A, second coil pair
 *  \param pin_2B GPIO to control coil B, second coil pair
 *  \param stepping_mode Firing sequence mode, single or power
 * 
 *  `pin_*` is each of four GPIOs used to control each coil pair in 
 *  the motor.
 * 
 *  `stepping_mode` selects the firing sequence for these four GPIOs.
 *  4-wire unipolar and bipolar motors can be stepped in "single" or
 *  "power" stepping. Power stepping provides more torque but uses
 *  more power. The stepping sequences are (after Scherz and Monk 2013,
 *  Fig 14.8):
 * 
 *  Single stepping      Power stepping
 *       Coil                 Coil
 *  Step 1A 1B 2A 2B     Step 1A 1B 2A 2B
 *     0  1  0  0  0        0  1  0  1  0
 *     1  0  0  1  0        1  0  1  1  0
 *     2  0  1  0  0        2  0  1  0  1
 *     3  0  0  0  1        3  1  0  0  1
 */
void stepper_init(stepper_t *s, uint8_t pin_1A, uint8_t pin_1B,
                  uint8_t pin_2A, uint8_t pin_2B,
                  uint16_t steps_per_revolution,
                  stepper_mode_t stepping_mode);


/*! \brief Set motor speed in RPM
 *
 *  \param s Pointer to a stepper_t structure 
 *  \param rpm Speed in revolutions per minute
 */
void stepper_set_speed_rpm(stepper_t *s, uint8_t rpm);


/*! \brief Rotate the motor one step
 *
 *  \param s Pointer to a stepper_t structure
 *  \param direction Which direction to step, 1 or -1
 */
void stepper_step_once(stepper_t *s, int8_t direction);


/*! \brief De-activate all coils
 *
 *  \param s Pointer to a stepper_t structure 
 */
void stepper_release(stepper_t *s);


/*! \brief Rotate the motor these many steps
 *
 *  \param s Pointer to a stepper_t structure
 *  \param steps How many steps to rotate. The sign indicates direction
 */
void stepper_rotate_steps(stepper_t *s, int16_t steps);


/*! \brief Rotate the motor these many degrees
 *
 *  \param s Pointer to a stepper_t structure
 *  \param degrees The degrees (angle) to rotate. The sign indicates direction
 * 
 *  Because the motor rotates at discrete steps, the actual angle rotated
 *  will often be an approximation to that requested, with an error that
 *  depends on the number of steps per revolution of the motor used. E.g. a
 *  motor with 200 steps per revolution will have an error of up to
 *  360/200 = 1.8 degrees.
 */
void stepper_rotate_degrees(stepper_t *s, float degrees);

#endif