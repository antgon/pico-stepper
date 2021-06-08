# pico-stepper

A C library for using a stepper motor with the Raspberry Pi Pico

Works with 4-wire bipolar or unipolar stepper motors. Two stepping modes have so far been implemented: "single" and "power" (see below).

## Wiring

Driving a stepper motor with the Pico (or pretty much any other microcontroller) requires a driver circuit, typically one H-bridge for each coil pair. There are many dual H-bridge motor driver breakout boards readily available (e.g. [Adafruit #2448](https://www.adafruit.com/product/2448)) and using one of these is an easy way to control a stepper motor with Pico.

Connect the stepper motor to the dual H-bridges board as per the board's instructions. Then connect the motor board to the Pico so that four of the Pico's GPIOs are used to control motor rotation.

## Software

1. Download **pico-stepper** library.

2. Create a Pico project. Edit `CMakeLists.txt` in your project to include the path to the **pico-stepper** library. E.g. if the **pico-stepper** library is located one directory above (`../`) your project then your `CMakeLists.txt` file should include these lines:
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

3. Use the stepper library in your project, e.g. (see the examples directory for full working code):
```c
.
.
.
#include "stepper.h"

stepper_t stepper;
const uint8_t stepper_pin_1A = 12;  // NOTE [1]
const uint8_t stepper_pin_1B = 13;
const uint8_t stepper_pin_2A = 14;
const uint8_t stepper_pin_2B = 15;
const uint8_t stepper_steps_per_revolution = 200;  // NOTE [2]
const stepper_mode_t stepping_mode = single;  // NOTE [3]

int main() {
    stdio_init_all();
    stepper_init(&stepper, stepper_pin_1A, stepper_pin_1B,
                 stepper_pin_2A, stepper_pin_2B,
                 stepper_steps_per_revolution, stepping_mode);
    stepper_set_speed_rpm(&stepper, 20);  // NOTE [4]

    while (true) {
        stepper_rotate_steps(&stepper, 200);  // NOTE [5]
        sleep_ms(1000);
        stepper_rotate_degrees(&stepper, -90);
        sleep_ms(1000);
    }
    return 0;
}
```

4. Compile your project and run.


### Notes

[1] These constants indicate the GPIOs that will control each of the four coils in the stepper. The number indicates a coil pair; i.e. in the example above GPIOs 12 and 13 will control the first coil pair (`stepper_pin_1x`), and GPIOs 14 and 15 will control the second coil pair (`stepper_pin_2x`).

[2] These are the number of steps needed for the motor to fully rotate once. This value depends on the specific motor used.

[3] Stepping mode can be `single` or `power`, and refers to the firing sequences used to step the motor: in single mode one coil is active at any one time, whereas in power mode two coils are powered at once. Power stepping provides more torque but uses more power [Scherz and Monk 2013]. In my experience, in power mode the motor turns more smoothly but it does get considerably hotter.

[4] This sets the rotation speed, in revolutions per minute (RPM).

[5] This function rotates the motor these many steps. If the number of steps is negative, the motor rotates in the oposite direction.

## References

Scherz and Monk, "Practical Electronics for Inventors" 3rd Ed., McGraw-Hill, 2013. (Sections 14.5 to 14.9 in that book are a very useful introduction to stepper motors.)