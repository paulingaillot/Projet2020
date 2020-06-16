#include <stdio.h>
#include <stdlib.h>
#include "UART.h"
#include <string.h>
#include "seven-seg.h"
#define MAXLENGTH 20

#ifdef PIC_VERSION
#include "pragma.h"
#include <xc.h>  // Needed by the MicroChip compiler
#define _XTAL_FREQ 20000000 // Define the MCU Frequency ; needed by the MicroChip compiler
#endif

void displayfree() {

#ifdef PIC_VERSION
    int value = eeprom_read(2);
    if(value != 0) {
        UART_Write_Text("Nombre de valeurs libres : ");
        UART_Write_Text(value);
    }
    else UART_Write_Text("Il n'y a plus d'espace disponible");
#endif
#ifndef PIC_VERSION
    printf("Desolé je ne peux pas afficher cela");
#endif

}

void setDefault(int val) {
#ifdef PIC_VERSION
    eeprom_write(3, val);
    UART_Write_Text(" La nouvelle phrase par default est la phrase numéro :");
    UART_Write_Text(val);
#endif
}

void setNextDefault() {
#ifdef PIC_VERSION
    int val = (eeprom_read(3)+1);
    eeprom_write(3, val);
    UART_Write_Text(" La nouvelle phrase par default est la phrase numéro : ");
    UART_Write_Text(val);
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

void addSentence(char* stc) {
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
    char lastval = ' ';
    for(int i=0; i< strlen(stc); i++) {
        UART_Write_Text("test 1");
        char val11 = stc[i];
        int val1 = 0;
        int val2=0;

        // Valeur a enregistrer
        if(val11 >=65 && val11 <=90) {
            val1 = tab1[val11-65];
            val2 = tab2[val11-65];
            eeprom_write(start+o, val1);
            eeprom_write(start+o+1, val2);
            o=o+2;
        }
        if(val11 >=48 && val11 <=57)  {
            val1 = tab1[26+val11-48];
            val2 = tab2[26+val11-48];
            eeprom_write(start+o, val1);
            eeprom_write(start+o+1, val2);
            o=o+2;
        }
        if(val11 == 32 && lastval != 32) {
            eeprom_write(start+o, 0);
            eeprom_write(start+o+1, 0);
            o=o+2;
        }
        lastval= val11;





    }
    UART_Write_Text("Votre phrase a bien été ajouté"git );
#endif
#ifndef PIC_VERSION
    UART_Write("Impossible");
#endif

}

void letter(int *tab, int size){
    if (tab == NULL){ return;}
    for (int i = 0; i < size; ++i) {
        if(tab[i]==0){
#ifdef PIC_VERSION
            __delay_ms(1000); // 1 second delay
            RD0 = 1; // LED ON
            __delay_ms(500); // 0.5 second delay
            RD0 = 0; // LED OFF
#endif
#ifndef PIC_VERSION
            printf(". ");
            // sleep(1);
#endif
        } else{
#ifdef PIC_VERSION
            __delay_ms(1000); // 1 second delay
            RD0 = 1; // LED ON
            __delay_ms(1500); // 1.5 second delay
            RD0 = 0; // LED OFF
#endif
#ifndef PIC_VERSION
            printf("- ");
            //sleep(1);
#endif
        }

    }
}

void convert(int length, int value) {
    int i = 0;
    int tabBits[8];
    char mask = 0b00000001;
    for (i = 8; i > (8-length); i--) {
        tabBits[i] = ((value & mask) != 0);
        mask <<= 1;
        printf("tabBits[%d]=%d\t", i, tabBits[i]);
    }
    letter(tabBits, length);
}

char getLetter(int val) {

    char res ;
    for(int i=0; i<=36; i++){
        int val1 = tab1[i];
        if(val == val1) {
            if(i<26){
               res = (char)(i+65);
            }else res = (char)((i-26)+48);

            return res;
        }
    }

}

void listsentence() {
#ifdef PIC_VERSION
    for(int i=6; i<=23; i=i+2) {
        int start = eeprom_read(i);
        for(int j =start; j<=(start+2*eeprom_read(i+1)); j=j+2) {
            int val = eeprom_read(24+start);
            int length = eeprom_read(24+start+1);

            convert(length, val);

            char letter = getLetter(val);

            UART_Write_Text("Playing the sequence on the physical display\n");
           display_7SEG(letter, LED_ONLY);
            UART_Write_Text("Playing the sequence on display & UART\n");
            display_7SEG(letter, UART_LED);

        }

    }
#endif
}

int main() {
    printf("Hello, World!\n");

    #ifdef PIC_VERSION
      OPTION_REG = (OPTION_REG & 0b01111111); // Activating pull-up on PORTB pins
      TRISB0 = 1;
      TRISD = 0x0;
      PORTD = 0x0;
    #endif

    #ifdef PIC_VERSION
        eeprom_write(0, 1);
        eeprom_write(1, 1);
        eeprom_write(2, 232);
        eeprom_write(3, 0);
        eeprom_write(4, 0);
        eeprom_write(5, 0);
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
                    "type a number.");

    char echo[MAXLENGTH];

    UART_Read_Text(echo, MAXLENGTH);

    UART_Write(echo);
    if(echo[0] == '1')  {

        UART_Write_Text("Veuillez taper la phrase a ajouter");

        char echo2[MAXLENGTH];
        UART_Read_Text(echo2, MAXLENGTH);

        addSentence(echo2);

    }
    if(echo[0] == '2') ;
    if(echo[0] == '3') ;
    if(echo[0] == '4')  {
        displayfree();
    }
    if(echo[0] == '5') ;
    if(echo[0] == '6') {

        char val[MAXLENGTH];
        UART_Read_Text(val, MAXLENGTH);

        setDefault((int)(val-48));

    }
    if(echo[0] == '7') {
        setNextDefault();
    }
    if(echo[0] == '8') {



    }



    return 0;
}
