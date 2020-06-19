//
// Created by isen on 4/24/20.
//
#include "version.h"
#include "seven-seg.h"
#include "UART.h"

#ifdef PIC_VERSION
#include <xc.h>
#endif

void physical_Display(char symbol) {

    unsigned char digitnumber[] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111,
                          0b01111111, 0b01101111};

    unsigned char digitletter[] = {
            0b01110111, 0b01111100, 0b00111001, 0b01011110, 0b01111001, 0b01110001, 0b00111101, 0b01110100, 0b00000100, 0b00001110,
            0b01110101, 0b00111000, 0b01010101, 0b01010100, 0b1011100, 0b01110011, 0b01100111, 0b01010000, 0b01101101, 0b01111000, 0b00111110,
            0b00011100, 0b01101010, 0b01110110, 0b01101110, 0b01011011
    };

    unsigned char segword;
    if ((symbol > 47) && (symbol < 58)) {
        segword = digitnumber[symbol - 48];
    }else if ( symbol >= 65 && symbol <=90 ){
        segword = digitletter[symbol - 65];
    } else
        segword = 0b01000000;
#ifdef PIC_VERSION
    PORTD = segword;;
#endif
}

void display_7SEG(unsigned char val, unsigned short mode) {
    if (mode == LED_ONLY || mode == UART_LED) {
        physical_Display(val);
    }
    if (mode == UART_ONLY || mode == UART_LED){
        if((val>=48 && val<=57) || (val>=65 && val<=90)) UART_Write(val);
        else UART_Write('-');
    }
}