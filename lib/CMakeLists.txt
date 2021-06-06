add_library(pico-stepper INTERFACE)

target_include_directories(pico-stepper
  INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(pico-stepper
  INTERFACE
)

target_sources(pico-stepper
  INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/stepper.c
  ${CMAKE_CURRENT_LIST_DIR}/include/stepper.h
)
