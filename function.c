//
// Created by Pauli on 18/06/2020.
//
#include "UART.h"
#include <string.h>
#include "seven-seg.h"
#include "version.h"
#include "function.h"

#define MAXLENGTH 10


#ifdef PIC_VERSION
#include "pragma.h"
#include <xc.h>  // Needed by the MicroChip compiler
#define _XTAL_FREQ 20000000 // Define the MCU Frequency ; needed by the MicroChip compiler
#endif



void displayfree() {

    unsigned short value = eeprom_read(2);
    if(value != 0) {
        UART_Write_Text("Nombre de valeurs libres : ");
        UART_Write_Text(value);
    }
    else UART_Write_Text("Il n'y a plus d'espace disponible");


}

void setDefault(unsigned short val) {

    unsigned short phrase = eeprom_read(1);

    if(val > phrase || val<0) {
        UART_Write_Text("THis sentence doesn't exist");
        return;
    }

    eeprom_write(3, val);
    UART_Write_Text(" The new sentence is the sentence number :");
    UART_Write((char)(val+48));

}

void setNextDefault() {

    unsigned short phrase = eeprom_read(1);

    if(eeprom_read(3)+1>phrase){
        UART_Write_Text("This sentence doesn't exist");
        return;
    }

    unsigned short val = (eeprom_read(3)+1);
    eeprom_write(3, val);
    UART_Write_Text(" La nouvelle phrase par default est la phrase numéro : ");
    UART_Write((char)(val+48));
}

unsigned short tab1[26]= {2, 4, 4, 3, 1, 4, 3, 4, 2, 4, 3, 4, 2, 2, 3, 4, 4, 3,
                          3, 1, 3, 4, 3, 4, 4, 4,
};

unsigned short tab2[36]= {0b00000010, 0b00000001,	0b00000101,	0b00000001,	0b00000000,	0b00000100,	0b00000011,	0b00000000,	0b00000000,	0b00001110,	0b00000101,	0b00000010,	0b00000011,	0b00000001,
                          0b00000111,	0b00000110,	0b00001011,	0b00000010,0b00000000,	0b00000001,	0b00000100,	0b00001000,	0b00000110,	0b00001001,	0b00001101,	0b00000011,
                          0b00011111,	0b00011110,	0b00011100,	0b00011000,	0b00010000,	0b00000000,	0b00000001,	0b00000011,	0b00000111,	0b00001111
};

void addSentence(char* stc) {

    unsigned short start = 24;
    unsigned short phrase = eeprom_read(1);

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
    eeprom_write(2, eeprom_read(2)-strlen(stc)*2); // ajout *2

    if(phrase == 0) {
        eeprom_write(6, start);
        eeprom_write(7, strlen(stc));
        UART_Write_Text("No definition in EEPROM");
    }
    else {
        unsigned short lStart = eeprom_read(6+2*(phrase-1));
        unsigned short llength = eeprom_read(7+2*(phrase-1))*2; // ajout *2
        start = lStart + llength;
        eeprom_write((6+2*(phrase-1))+2, start);
        eeprom_write((7+2*(phrase-1))+2, strlen(stc));
    }

    char lastVal = ' ';
    unsigned short o=0;
    for(int i=0; i< strlen(stc); i++) {

        char value = stc[i];

        if(value>=97 && value <=122) {
            value = value - 32;
        }

        if(value >=65 && value <=90) {
            unsigned short val1 = tab2[value-65];
            unsigned short val2 = tab1[value-65];

            eeprom_write(start+o, val1);

            eeprom_write(start+o+1, val2);
            o=o+2;
        }
        else if(value >=48 && value <=57)  {
            unsigned short val1 = tab2[26+value-48];
            unsigned short val2 = 5;
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


}

void letter(unsigned short *tab, unsigned short size){

    if(size == 0){
        __delay_ms(2800); // 1 second delay
        return;
    }

    for (unsigned short i = 0; i < size; ++i) {



        if(tab[i]==0){
#ifdef PIC_VERSION
            UART_Write('.');
            __delay_ms(400); // 1 second delay
            RC0 = 1; // LED ON
            __delay_ms(400); // 0.5 second delay
            RC0 = 0; // LED OFF
#endif
#ifndef PIC_VERSION
            printf(". ");
            // sleep(1);
#endif
        } else{
#ifdef PIC_VERSION
            UART_Write('-');
            __delay_ms(400); // 1 second delay
            RC0 = 1; // LED ON
            __delay_ms(1200); // 1.5 second delay
            RC0 = 0; // LED OFF
#endif
#ifndef PIC_VERSION
            printf("- ");
            //sleep(1);
#endif
        }

    }
}

void convert(unsigned short length, unsigned short value) {
    unsigned short i = 0;
    unsigned short tabBits[8] = {0};
    char mask = 0b00000001;
    for (i = 8; i > (8-length); i--) {
        tabBits[i] = ((value && mask) != 0);
        mask <<= 1;
    }

    unsigned short tabBits2[8] = {0};
    for(unsigned short i=0; i<8; i++){
        tabBits2[i] = tabBits2[8-i];
    }

    letter(tabBits2, length);
}

char getLetter(unsigned short val, unsigned short length) {

    char res = 'A';
    for(unsigned short i=0; i<=36; i++){
        unsigned short val1 = tab2[i];

        unsigned short length1 = 5;
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
    unsigned short phrase = eeprom_read(1);

    if(phrase == 0) {
        UART_Write_Text("Il n'y a aucune phrase enregistrer");
        return;
    }

    for(unsigned short i=0; i<phrase; i++){

        unsigned short start = eeprom_read(6+i*2);
        unsigned short length = eeprom_read(7+i*2);

        for(unsigned short j=start; j<(start+length*2); j=j+2){

            unsigned short val = eeprom_read(j);
            unsigned short length2 = eeprom_read(j+1);
            char let = getLetter(val, length2);

            display_7SEG(let, UART_LED);
            convert(length2, val);

        }

    }
#endif
}

void listsentence() {
    unsigned short phrase = eeprom_read(1);

    if(phrase == 0) {
        UART_Write_Text("Il n'y a aucune phrase enregistrer");
        return;
    }

    for(unsigned short i=0; i<phrase; i++){

        unsigned short start = eeprom_read(6+i*2);
        unsigned short length = eeprom_read(7+i*2);

        for(unsigned short j=start; j<(start+length*2); j=j+2){


            unsigned short val = eeprom_read(j);
            unsigned short length2 = eeprom_read(j+1);
            char let = getLetter(val, length2);

            UART_Write(let);

        }
        UART_Write_Text("\n");

    }
}

void delete(unsigned short val) {

    unsigned short phrase = eeprom_read(1);

    if(val > phrase || phrase == 0){
        UART_Write_Text("Delete error : cannot delete an ghost sentence");
        return;
    }

    unsigned short taille = eeprom_read(7+2*(val-1))*2; // ajout *2

    if(val != phrase){
        unsigned short start = eeprom_read(6+2*(val-1));
        unsigned short next = eeprom_read(6+2*(val));
        unsigned short endOfUART = eeprom_read(6+2*(phrase-1))+eeprom_read(7+2*(phrase-1))*2; // ajout *2
        unsigned short sizeOfUART = endOfUART-next;

        for(int i=(6+2*(val-1)); i<(6+2*phrase)-2; i=i+2){
            eeprom_write(i, (eeprom_read(i+2)-taille));
            eeprom_write(i+1, eeprom_read(i+3));
        }
        eeprom_write(6+2*(phrase-1), 0);
        eeprom_write(7+2*(phrase-1), 0);


        for(unsigned short i=0; i<sizeOfUART; i++){
            eeprom_write(start+i, eeprom_read(next+i));
        }
    }
    else{
        eeprom_write(6+2*(val-1), 0);
        eeprom_write(7+2*(val-1), 0);
    }
    unsigned short nbFreeCell = eeprom_read(2);
    eeprom_write(2, nbFreeCell+(taille));
    eeprom_write(1, eeprom_read(1)-1);

    UART_Write_Text("Sentence Delete");

}

void playDefault() {

#ifdef PIC_VERSION
    unsigned short phrase = eeprom_read(1);

    if(phrase == 0) {
        UART_Write_Text("Il n'y a aucune phrase enregistrer");
        return;
    }

    int defaut = eeprom_read(3);

    if(defaut == 0) {
        UART_Write_Text("No default sentence set");
        return;
    }

    unsigned short start = eeprom_read(6+(defaut-1)*2);
    unsigned short length = eeprom_read(7+(defaut-1)*2);

    for(unsigned short j=start; j<(start+length*2); j=j+2){

        unsigned short val = eeprom_read(j);
        unsigned short length2 = eeprom_read(j+1);
        char let = getLetter(val, length2);

        display_7SEG(let, UART_LED);
        convert(length2, val);

    }


#endif

}
