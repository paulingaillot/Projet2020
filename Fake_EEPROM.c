//
// Created by isen on 4/22/20.
//
#include "Fake_EEPROM.h"

unsigned char EEPROM[256]={0};

unsigned short eeprom_read(unsigned short position) {
    return EEPROM[position];
}

void eeprom_write(unsigned short position, unsigned short value){
    if (position < 255) {
        EEPROM[position]=value;
    }
}
