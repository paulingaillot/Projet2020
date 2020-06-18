#include <stdio.h>
#include <stdlib.h>
#include "UART.h"
#include "function.h"
#include "version.h"
#define MAXLENGTH 10


#ifdef PIC_VERSION
#include "pragma.h"
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

          eeprom_write(0, 1);
          eeprom_write(1, 0);
          eeprom_write(2, 232);
          eeprom_write(3, 0);
          eeprom_write(4, 0);
          eeprom_write(5, 0);

    UART_Init();

    while(1){
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

        switch(echo[0]) {

            case '1': {

                UART_Write_Text(" Please input a new phrase:\n");

                char echo2[MAXLENGTH];
                UART_Read_Text(echo2, MAXLENGTH);


                addSentence(echo2);
                break;

            }
            case '2': {

                UART_Write_Text("« Please input the number of the sentence to delete:\n");

                char val[MAXLENGTH];
                UART_Read_Text(val, MAXLENGTH);

                delete((int) (val[0] - 48));
                break;

            }
            case '3': {
                listsentence();
                break;
            }
            case '4': {
                displayfree();
                break;
            }
            case '5': {

                playDefault();
                break;

            }
            case '6': {

                UART_Write_Text("Please input the number of the phrase to set default :\n");

                char val[MAXLENGTH];
                UART_Read_Text(val, MAXLENGTH);

                setDefault((int) (val[0] - 48));
                break;

            }
            case '7': {


                setNextDefault();
                break;
            }
            case '8': {

                playAll();
                break;

            }
        }
    }




    return 0;
}
