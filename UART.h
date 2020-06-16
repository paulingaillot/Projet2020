//
// Created by isen on 4/22/20.
//
#include "version.h"

#ifndef UART_H
#define UART_H
void UART_Clear_Buffer(void);
void UART_Init(void );
void UART_Write(char data);
void UART_Write_Text(char* text);
char UART_Read(void );
void UART_Read_Text(char* Output, unsigned int length );
#ifdef PIC_VERSION
char UART_TX_Empty(void);
char UART_Data_Ready(void);
#endif
#endif //V1_UART_H
