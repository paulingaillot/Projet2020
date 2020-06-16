//
// Created by isen on 4/24/20.
//

#ifndef SEVEN_SEG_H
#define SEVEN_SEG_H
// Digit Display options
#define UART_ONLY 0
#define LED_ONLY 1
#define UART_LED 2

void physical_Display(char symbol);
void display_7SEG(char val, unsigned short mode);
#endif
