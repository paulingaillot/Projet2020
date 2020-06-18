cmake_minimum_required(VERSION 3.13)
project(Projet C)

set(CMAKE_C_STANDARD 11)

add_executable(Projet main.c UART.c seven-seg.c menu.h Fake_EEPROM.c Fake_EEPROM.h menu.c menu.h function.c function.h)