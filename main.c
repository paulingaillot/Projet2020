#include <stdio.h>
#include <stdlib.h>
#include "UART.h"
#include <string.h>
#include "seven-seg.h"
#define MAXLENGTH 20

#ifdef PIC_VERSION
#include "pragma.h"
#include "menu.h"
#include <xc.h>  // Needed by the MicroChip compiler
#define _XTAL_FREQ 20000000 // Define the MCU Frequency ; needed by the MicroChip compiler
#endif

int main() {

    #ifdef PIC_VERSION
      OPTION_REG = (OPTION_REG & 0b01111111); // Activating pull-up on PORTB pins
      TRISB0 = 1;
      TRISC0 = 0;
      TRISD = 0x0;
      PORTD = 0x0;
    #endif

    #ifdef PIC_VERSION
      if(eeprom_read(0) == 0) {
          eeprom_write(0, 1);
          eeprom_write(1, 0);
          eeprom_write(2, 232);
          eeprom_write(3, 0);
          eeprom_write(4, 0);
          eeprom_write(5, 0);
      }
    #endif


    UART_Init();


    UART_Write_Text("----- Menu -----\n"
                    "1- add a sentence\n"
                    "2- delete a sentence\n"
                    "3- list sentences\n"
                    "4- display amount of free sells\n" // Done
                    "5- blink default sentences\n"
                    "6- set the default setence\n" // Done
                    "7- set next setence as default\n" //Done
                    "8- play all the sentences\n"
                    "type a number.\n");

    char echo[MAXLENGTH];

    UART_Read_Text(echo, MAXLENGTH);


    if(echo[0] == '1')  {

        UART_Write_Text(" Please input a new phrase:\n");

        char echo2[MAXLENGTH];
        UART_Read_Text(echo2, MAXLENGTH);


        addSentence(echo2);

    }
    if(echo[0] == '2')  {

        UART_Write_Text("« Please input the number of the sentence to delete:\n");

        char val[MAXLENGTH];
        UART_Read_Text(val, MAXLENGTH);

        delete((int)(val[0]-48));

    }
    if(echo[0] == '3')  {
        listsentence();
    }
    if(echo[0] == '4')  {
        displayfree();
    }
    if(echo[0] == '5')  {

        playDefault();

    }
    if(echo[0] == '6') {

        UART_Write_Text("Please input the number of the phrase to set default :\n");

        char val[MAXLENGTH];
        UART_Read_Text(val, MAXLENGTH);

        setDefault((int)(val[0]-48));

    }
    if(echo[0] == '7') {


        setNextDefault();
    }
    if(echo[0] == '8') {

        playAll();

    }



    return 0;
}
