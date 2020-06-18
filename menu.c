//
// Created by Pauli on 18/06/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include <string.h>
#include <xc.h>
#include "UART.h"
#include "pragma.h"
#include "seven-seg.h"
#define MAXLENGTH 20
#define _XTAL_FREQ 20000000 // Define the MCU Frequency ; needed by the MicroChip compiler

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

    int phrase = eeprom_read(1);

    if(val > phrase || val<0) {
        UART_Write_Text("THis sentence doesn't exist");
        return;
    }

    eeprom_write(3, val);
    UART_Write_Text(" The new sentence is the sentence number :");
    UART_Write((char)(val+48));
#endif
}

void setNextDefault() {
#ifdef PIC_VERSION

    int phrase = eeprom_read(1);

    if(eeprom_read(3)+1>phrase){
        UART_Write_Text("This sentence doesn't exist");
        return;
    }

    int val = (eeprom_read(3)+1);
    eeprom_write(3, val);
    UART_Write_Text(" La nouvelle phrase par default est la phrase numéro : ");
    UART_Write((char)(val+48));
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
    UART_Write((char)(phrase+48));
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
        start = lStart + llength*2 + 1;
        eeprom_write((6+2*(phrase-1))+2, start);
        eeprom_write((6+2*(phrase-1))+3, strlen(stc));
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

            display_7SEG(let, UART_LED);
            convert(length2, val);

        }

    }
#endif
}

void listsentence() {
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

            UART_Write(let);

        }
        UART_Write_Text("\n");

    }
#endif
}

void delete(int val) {
#ifdef PIC_VERSION
    int phrase = eeprom_read(1);

    if(val > phrase){
        UART_Write_Text("Delete error : cannot delete an ghost sentence");
        return;
    }

    int taille = eeprom_read(7+2*(val-1));

    if(val == phrase){
        eeprom_write(1, (eeprom_read(1)-1));
    }
    else {
        eeprom_write(2, (eeprom_read(2)-eeprom_read(6+2*(val-1))));

        int start = eeprom_read(6+2*(val-1));
        int next = eeprom_read(6+2*(val));

        for(int i=(6+2*(val-1)); i<(6+2*phrase); i=i+2){
            eeprom_write(i, (eeprom_read(i+2)-2*taille));
            eeprom_write(i+1, i+3);
        }

        for(int i=0; i<(eeprom_read(6+2*(phrase-1))+eeprom_read(7+2*(phrase-1))); i++){
            eeprom_write(start+i, eeprom_read(next+i));
        }
        eeprom_write(1, (eeprom_read(1)-1));

    }

    UART_Write_Text("Sentence Delete");


#endif


}

void playDefault() {

#ifdef PIC_VERSION
    int phrase = eeprom_read(1);

    if(phrase == 0) {
        UART_Write_Text("Il n'y a aucune phrase enregistrer");
        return;
    }

    int defaut = eeprom_read(3);

    if(defaut == 0) {
        UART_Write_Text("No default sentence set");
        return;
    }

    int start = eeprom_read(6+(defaut-1)*2);
    int length = eeprom_read(7+(defaut-1)*2);

    for(int j=start; j<(start+length*2); j=j+2){

        int val = eeprom_read(j);
        int length2 = eeprom_read(j+1);
        char let = getLetter(val, length2);

        display_7SEG(let, UART_LED);
        convert(length2, val);

    }


#endif

}
