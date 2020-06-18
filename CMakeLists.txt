cmake_minimum_required(VERSION 3.13)
project(Projet C)

set(CMAKE_C_STANDARD 11)

add_executable(Projet main.c UART.c seven-seg.c Fake_EEPROM.c Fake_EEPROM.h function.c function.h)