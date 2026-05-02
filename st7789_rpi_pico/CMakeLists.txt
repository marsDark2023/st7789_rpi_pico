set(P "test_pico_6")
cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(${P} C CXX ASM)
add_executable(${P} main.c)
target_sources( ${P} PRIVATE lcd.c spi.c)
target_include_directories( ${P} PRIVATE ./include)

pico_sdk_init()
	
pico_enable_stdio_usb(${P} 1)
pico_enable_stdio_uart(${P} 0)

target_link_libraries(${P} pico_stdlib pico_multicore hardware_exception)
pico_add_extra_outputs(${P})
