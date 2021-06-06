# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_SDK_PATH "/home/antgon/pico/pico-sdk")
# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

# Add pico-stepper directory
add_subdirectory(../lib stepper)

project(stepper-basic-example C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1
add_executable(stepper-basic-example stepper-basic-example.c)

pico_set_program_name(stepper-basic-example "stepper-basic-example")
pico_set_program_version(stepper-basic-example "0.1")

# This stdio configuration alows to see the Pico output when connected to a
# picoprobe. Enable usb and disable uart for standalone operation (direct USB
# connection).
pico_enable_stdio_uart(stepper-basic-example 1)
pico_enable_stdio_usb(stepper-basic-example 0)

# Standard and additional libraries
target_link_libraries(stepper-basic-example
	pico_stdlib
	pico-stepper)

pico_add_extra_outputs(stepper-basic-example)

