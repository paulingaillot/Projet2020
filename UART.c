//
// Created by isen on 4/22/20.
//
#include "version.h"
#include "function.h"
#ifndef PIC_VERSION
#include <stdio.h>
#endif
#ifdef PIC_VERSION
#include <xc.h>
#define _XTAL_FREQ 20000000
#endif
#include "UART.h"


void UART_Clear_Buffer(){
#ifndef PIC_VERSION
    while(getchar()!='\n');
#endif
#ifdef PIC_VERSION
    char c;
    __delay_ms(200);
    while (UART_Data_Ready()) {
        c=RCREG;
        __delay_ms(200);
    }
#endif
}

void UART_Init() {
#ifndef PIC_VERSION
    printf("UART initialized\n");
#endif
#ifdef PIC_VERSION
    BRGH = 1;       //Setting High Baud Rate as prescribed in Datasheet
    SPBRG = 129;    // 9600 Bauds as defined in Datasheet
    SYNC = 0;       //Setting Asynchronous Mode, ie UART
    SPEN = 1;       //Enables Serial Port
    TRISC7 = 1;     //As Prescribed in Datasheet
    TRISC6 = 1;     //As Prescribed in Datasheet
    CREN = 1;       //Enables Continuous Reception
    TXEN = 1;       //Enables Transmission
#endif
}

void UART_Write(char data) {
#ifndef PIC_VERSION
    printf("%c",data);
#endif
#ifdef PIC_VERSION
    while(!TRMT) ;
    TXREG = data;
#endif
}

void UART_Write_Text(char* text) {
#ifndef PIC_VERSION
    printf("%s",text);
    fflush(stdout);
#endif
#ifdef PIC_VERSION
    int i;
    for(i=0;text[i]!='\0';i++)
        UART_Write(text[i]);
#endif
}

char UART_Read() {
#ifndef PIC_VERSION
    return (char) getchar();
#endif
#ifdef PIC_VERSION
    while(!RCIF) {
        if(RB0 == 0) {
            playDefault();
        }
    }

    return RCREG;
#endif
}

void UART_Read_Text(char* Output, unsigned int length ) {
    unsigned int i;
    char tmp;
    for (i=0 ; i<length-1 ; i++) {
        tmp = UART_Read();
        if (tmp == '#') {
            break;
        }
        Output[i] = tmp;
    }
    Output[i] = '\0';
    UART_Clear_Buffer();

}

#ifdef PIC_VERSION

char UART_Data_Ready(void) {
    return RCIF;
}
#endif