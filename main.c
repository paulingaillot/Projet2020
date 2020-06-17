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

int tab1[26]= {2, 4, 4, 3, 1, 4, 3, 4, 2, 4, 3, 4, 2, 2, 3, 4, 4, 3,
            3, 1, 3, 4, 3, 4, 4, 4,
};

int tab2[36]= {0b00000010, 0b00000001,	0b00000101,	0b00000001,	0b00000000,	0b00000100,	0b00000011,	0b00000000,	0b00000000,	0b00001110,	0b00000101,	0b00000010,	0b00000011,	0b00000001,
            0b00000111,	0b00000110,	0b00001011,	0b00000010,0b00000000,	0b00000001,	0b00000100,	0b00001000,	0b00000110,	0b00001001,	0b00001101,	0b00000011,
            0b00011111,	0b00011110,	0b00011100,	0b00011000,	0b00010000,	0b00000000,	0b00000001,	0b00000011,	0b00000111,	0b00001111
};

void addSentence(char* stc) {
#ifdef PIC_VERSION

    int start = 24;
    int phrase = eeprom_read(1);

    if(phrase == 9) {
        UART_Write_Text("Add error: could not save new phrase");
        return;
    }
    if(strlen(stc) > eeprom_read(2)) {
        UART_Write_Text("Add error: could not save new phrase");
        return;
    }
    if(strlen(stc) < 1){
        UART_Write_Text("Can’t store Empty String");
    }

    UART_Write_Text("Adding phrase : ");
    UART_Write_Text(stc);
    UART_Write_Text("in position ");
    UART_Write_Text(phrase);
    UART_Write_Text("\n");

    eeprom_write(1, (phrase+1));
    eeprom_write(2, eeprom_read(2)-strlen(stc));

    if(phrase == 0) {
        eeprom_write(6, start);
        eeprom_write(7, strlen(stc));
        UART_Write_Text("No definition in EEPROM");
    }
    else {
        int lStart = eeprom_read(6+2*(phrase-1));
        int llength = eeprom_read(7+2*(phrase-1));
        start = lStart + llength+ 1;
        eeprom_write(lStart+2, start);
        eeprom_write(llength+2, strlen(stc));
    }

    char lastVal = ' ';
    int o=0;
    for(int i=0; i< strlen(stc); i++) {

        char value = stc[i];

        if(value>=97 && value <=122) {
            value = value - 32;
        }

         if(value >=65 && value <=90) {
            int val1 = tab2[value-65];
            int val2 = tab1[value-65];

            eeprom_write(start+o, val1);

            eeprom_write(start+o+1, val2);
            o=o+2;
        }
        else if(value >=48 && value <=57)  {
            int val1 = tab2[26+value-48];
            int val2 = 5;
            eeprom_write(start+o, val1);
            eeprom_write(start+o+1, val2);
            o=o+2;
        }
        else if(value == 32 && lastVal != 32) {
            eeprom_write(start+o, 0);
            eeprom_write(start+o+1, 0);
            o=o+2;
        }

        lastVal= value;
    }

    UART_Write_Text("New phrase saved");

#endif
#ifndef PIC_VERSION
    UART_Write(stc[0]);
#endif

}

void letter(int *tab, int size){
    if (tab == NULL){ return;}
    for (int i = 0; i < size; ++i) {
        if(tab[i]==0){
#ifdef PIC_VERSION
            __delay_ms(1000); // 1 second delay
            RC0 = 1; // LED ON
            __delay_ms(500); // 0.5 second delay
            RC0 = 0; // LED OFF
#endif
#ifndef PIC_VERSION
            printf(". ");
            // sleep(1);
#endif
        } else{
#ifdef PIC_VERSION
            __delay_ms(1000); // 1 second delay
            RC0 = 1; // LED ON
            __delay_ms(1500); // 1.5 second delay
            RC0 = 0; // LED OFF
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
        UART_Write_Text(tabBits[i]);
    }

    int tabBits2[8];
    for(int i=0; i<8; i++){
        tabBits2[i] = tabBits2[8-i];
    }

    letter(tabBits2, length);
}

char getLetter(int val, int length) {

    char res = 'A';
    for(int i=0; i<=36; i++){
        int val1 = tab2[i];

        int length1 = 5;
        if(i<=25)  length1 = tab1[i];
        else length1 = 5;

        if(val == val1 && length1 == length) {
            if(i<26){
               res = (char)(i+65);
            }else res = (char)((i-26)+48);

            return res;
        }
    }

}

void playAll() {
#ifdef PIC_VERSION
    int phrase = eeprom_read(1);

    if(phrase == 0) {
        UART_Write_Text("Il n'y a aucune phrase enregistrer");
        return;
    }

    for(int i=0; i<phrase; i++){

        int start = eeprom_read(6+i*2);
        int length = eeprom_read(7+i*2);

        for(int j=start; j<(start+length*2); j=j+2){

            int val = eeprom_read(j);
            int length2 = eeprom_read(j+1);
            char let = getLetter(val, length2);


            convert(length2, val);
            //display_7SEG(let, UART_LED);

        }

    }
#endif
}

void listsentence() {
#ifdef PIC_VERSION

    for(int i=24; i<35; i++) {

        int val = eeprom_read(24+i);
        int length = eeprom_read(24+i+1);

            convert(length, val);

           UART_Write_Text("Playing the sequence on the physical display\n");
           display_7SEG(getLetter(val, length), LED_ONLY);
            UART_Write_Text("Playing the sequence on display & UART\n");
            display_7SEG(getLetter(val, length), UART_LED);
            display_7SEG(getLetter(val, length), UART_LED);

    }

    /*int phrase = eeprom_read(1);
    for(int i=6; i<=(6+(phrase-1)*2+1); i=i+2) {
        int start = eeprom_read(i);
        for(int j =start; j<=(start+2*eeprom_read(i+1)); j=j+2) {
            int val = eeprom_read(24+start);
            int length = eeprom_read(24+start+1);

            convert(length, val);

            char letter = getLetter(val, lenth);

            UART_Write_Text("Playing the sequence on the physical display\n");
           display_7SEG(letter, LED_ONLY);
            UART_Write_Text("Playing the sequence on display & UART\n");
            display_7SEG(letter, UART_LED);
            __delay_ms(1000);
        }

    }*/
#endif
}

int main() {
    printf("Hello, World!\n");

    #ifdef PIC_VERSION
      OPTION_REG = (OPTION_REG & 0b01111111); // Activating pull-up on PORTB pins
      TRISB0 = 1;
      TRISC0 = 0;
      TRISD = 0x0;
      PORTD = 0x0;
    #endif

    #ifdef PIC_VERSION
      if(eeprom_read(0) != 1) {
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

    UART_Write(echo);
    if(echo[0] == '1')  {

        UART_Write_Text("« Please input a new phrase:\n");

        char echo2[MAXLENGTH];
        UART_Read_Text(echo2, MAXLENGTH);


        addSentence(echo2);

    }
    if(echo[0] == '2')  {

    }
    if(echo[0] == '3')  {
        listsentence();
    }
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

        playAll();

    }



    return 0;
}
