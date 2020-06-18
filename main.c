#include <stdio.h>
#include <stdlib.h>
#include "UART.h"
#include "function.h"
#include "version.h"
#define MAXLENGTH 20


#ifdef PIC_VERSION
#include "pragma.h"
#include <xc.h>  // Needed by the MicroChip compiler
#define _XTAL_FREQ 20000000 // Define the MCU Frequency ; needed by the MicroChip compiler
#endif
#ifndef PIC_VERSION
#include "Fake_EEPROM.h"
#endif


int main() {

    #ifdef PIC_VERSION
      OPTION_REG = (OPTION_REG & 0b01111111); // Activating pull-up on PORTB pins
      TRISB0 = 1;
      TRISC0 = 0;
      TRISD = 0x0;
      PORTD = 0x0;
    #endif

          eeprom_write(0, 1);
          eeprom_write(1, 0);
          eeprom_write(2, 232);
          eeprom_write(3, 0);
          eeprom_write(4, 0);
          eeprom_write(5, 0);

    UART_Init();

    while(1){

        #ifdef PIC_VERSION
           PORTD = 0x0;
        #endif

           UART_Write_Text("\nEnter a command\n");

        char echo[MAXLENGTH];

        UART_Read_Text(echo, MAXLENGTH);

        switch(echo[0]) {

            case 'a': {

                UART_Write_Text(" Please input a new phrase:\n");

                char echo2[MAXLENGTH];
                UART_Read_Text(echo2, MAXLENGTH);


                addSentence(echo2);
                break;

            }
            case 'd': {

                if(eeprom_read(1) !=0) UART_Write_Text("Entry to delete: \n");
                else UART_Write_Text("deleteError : No phrase stored ");

                char val[MAXLENGTH];
                UART_Read_Text(val, MAXLENGTH);

                delete((int) (val[0] - 48));
                break;

            }
            case 'l': {
                listsentence();
                break;
            }
            case 'f': {
                displayfree();
                break;
            }
            case '$': {

                #ifndef PIC_VERSION
                return 0;
                #endif
                break;
            }
            case 'h': {
                UART_Write_Text("\n----- Menu -----\n"
                                "h- Show the help message (this one)"
                                "a- add a sentence\n"
                                "d- delete a sentence\n"
                                "l- list sentences\n"
                                "f- display amount of free sells\n" // Done
                                "r- play the default sentences\n"
                                "s- set the default sentence\n" // Done
                                "n- set next sentence as default\n" //Done
                                "p- play all the sentences\n"
                                "$- Stop the program (Only for PC)\n");
                break;
            }
            case 'r': {

                playDefault();
                break;

            }
            case 's': {

                UART_Write_Text("Please input the number of the phrase to set default :\n");

                char val[MAXLENGTH];
                UART_Read_Text(val, MAXLENGTH);

                setDefault((int) (val[0] - 48));
                break;

            }
            case 'n': {


                setNextDefault();
                break;
            }
            case 'p': {

                playAll();
                break;

            }
        }
    }
}
