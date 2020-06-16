#include <stdio.h>
#include "UART.h"
#include <string.h>
#define MAXLENGTH 20

#ifdef PIC_VERSION
#include "pragma.h"
#include <xc.h>  // Needed by the MicroChip compiler
#define _XTAL_FREQ 20000000 // Define the MCU Frequency ; needed by the MicroChip compiler
#endif

void displayfree() {

#ifdef PIC_VERSION
    int value = eeprom_read(2);
    if(value != 0) UART_Write_Text("Nombre de valeurs libres : %d", value);
    else UART_Write_Text("Il n'y a plus d'espace disponible");
#endif
#ifndef PIC_VERSION
    printf("Desolé je ne peux pas afficher cela");
#endif

}

void setDefault(int val) {
#ifdef PIC_VERSION
    eeprom_write(3, val);
    UART_Write_Text(" La nouvelle phrase par default est la phrase numéro : %d", val);
#endif
}

void setNextDefault() {
#ifdef PIC_VERSION
    int val = (eeprom_read(3)+1);
    eeprom_write(3, val);
    UART_Write_Text(" La nouvelle phrase par default est la phrase numéro : %d", val);
#endif
}

int* tab1= {2, 4, 4, 3, 1, 4, 3, 4, 2, 4, 3, 4, 2, 2, 3, 4, 4, 3,
            3, 1, 3, 4, 3, 4, 4, 4,
            5, 5, 5, 5, 5, 5, 5, 5, 5, 5
};

int* tab2= {0b00000010, 0b00000001,	0b00000101,	0b00000001,	0b00000000,	0b00000100,	0b00000011,	0b00000000,	0b00000000,	0b00001110,	0b00000101,	0b00000010,	0b00000011,	0b00000001,
            0b00000111,	0b00000110,	0b00001011,	0b00000010,0b00000000,	0b00000001,	0b00000100,	0b00001000,	0b00000110,	0b00001001,	0b00001101,	0b00000011,
            0b00011111,	0b00011110,	0b00011100,	0b00011000,	0b00010000,	0b00000000,	0b00000001,	0b00000011,	0b00000111,	0b00001111
};

void addsetnence(char* stc) {
#ifdef PIC_VERSION
    int j=0;
    int start =24;
    int test= 1;

    int phrase = eeprom_read(1);

    if(phrase != 0) start = eeprom_read(6+2*(phrase-1))+eeprom_read(7+2*(phrase-1))+1;
    else start = 24;

    eeprom_write(j+6, start);
    eeprom_write(j+7, strlen(stc));

    int o=0;
    for(int i=0; i< strlen(stc); i++) {

        char val11 = stc[i];
        int val1 = 0;
        int val2=0;

        // Valeur a enregistrer

        if(val11 >=65 && val11 <=90) val1 = tab1[val11-65];
        if(val11 >=48 && val11 <=57) val1 = tab1[26+val11-48];

        if(val11 >=65 && val11 <=90) val2 = tab2[val11-65];
        if(val11 >=48 && val11 <=57) val2 = tab2[26+val11-48];

        eeprom_write(start+o, val1);
        eeprom_write(start+o+1, val2);
        o=o+2;

    }
#endif
#ifndef PIC_VERSION
    UART_Write("Impossible");
#endif

}

void listsentence() {
#ifdef PIC_VERSION
    for(int i=6; i<=23; i=i+2) {
        int start = eeprom_read(i);
        for(int j =start; j<=(start+eeprom_read(i+1)); j++) {
            int val = eeprom_read(24+start);
            char letter = getLetter(val);
        }

    }
#endif
}

int main() {
    printf("Hello, World!\n");

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
                    "type a number.");

    char echo[MAXLENGTH];

    UART_Read_Text(echo, MAXLENGTH);

    if(echo == '1') ;
    if(echo == '2') ;
    if(echo == '3') ;
    if(echo == '4') ;
    if(echo == '5') ;
    if(echo == '6') ;
    if(echo == '7') ;
    if(echo == '8') ;



    return 0;
}
