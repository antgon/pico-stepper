# pico-stepper

A C library for using a stepper motor with the Raspberry Pi Pico

Works with 4-wire bipolar or unipolar stepper motors. Two stepping modes have so far been implemented: "single" and "power". "Power" stepping mode provides more torque but uses more power.

## Wiring

Driving a stepper motor with the Pico (or any other mcrocontroller) requires a driver circuit, typically one H-bridge for each coil pair. There are many dual H-bridge motor driver breakout boards readily available (e.g. [Adafruit #2448](https://www.adafruit.com/product/2448)) and using one of these is an easy way to control a motor with Pico.

Connect the stepper motor to the dual H-bridges board as required (usually this iincludes adding an external power source for the motor). Connect the motor board to the Pico so that four of the Pico's GPIOs are used to control the motor's rotation. The motor breakout board's instructions should make all this clearer.

## Software

1. Download the stepper library.

2. Create a Pico project and use the stepper library as in e.g.
(see the examples directory for the full working code):
```c
.
.
.
#include "stepper.h"

stepper_t stepper;
const uint8_t stepper_pin_1A = 12;
const uint8_t stepper_pin_1B = 13;
const uint8_t stepper_pin_2A = 14;
const uint8_t stepper_pin_2B = 15;
const uint8_t stepper_steps_per_revolution = 200;
const stepper_mode_t stepping_mode = single;

int main() {
    stdio_init_all();
    stepper_init(&stepper, stepper_pin_1A, stepper_pin_1B,
                 stepper_pin_2A, stepper_pin_2B,
                 stepper_steps_per_revolution, stepping_mode);
    stepper_set_speed_rpm(&stepper, 20);

    while (true) {
        stepper_rotate_steps(&stepper, 100);
        sleep_ms(1000);
        stepper_rotate_degrees(&stepper, -90);
        sleep_ms(1000);
    }
    return 0;
}
```

3. Edit `CMakeLists.txt` in your project to include the path to the **pico-stepper** library: add **pico-stepper** to the list of target libraries. E.g. if the **pico-stepper** library is located one directory above (`../`) your project then your `CMakeLists.txt` file should include these lines:
```cmake
.
.
.
include(pico_sdk_import.cmake)
add_subdirectory(../pico-stepper/lib stepper)

target_link_libraries(<name-of-your-project>
        pico_stdlib
        pico-stepper
)
.
.
.
```

4. Compile your project and run.


## Notes and credits

Stepper firing sequences are based on Fig.14.8 in Scherz and Monk "Practical Electronics for Inventors" 3rd Ed., McGraw-Hill, 2013. Sections 14.5 to 14.9 in that book are a very useful introduction to stepper motors.

The basic algorithm used here to step the motor is based on Arduino Stepper library (Version 1.1.0).