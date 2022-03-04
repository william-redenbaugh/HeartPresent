/*
function: cardReader.h
Description of .h file: \
This file handles everything involving card reader. 
*/
#ifndef _CARDREADER_H
#define _CARDREADER_H

#include "MFRC522.h"
#include "Particle.h"

// PIN DENOMINATIONS // 
#define SS_PIN SS
#define RST_PIN D2

class rfidReader{
    public: 
        /*
        function: setupCardReader()
        description:initializes the card reader, and card reader spi settings
        parameters: none
        returns: none
        */
        void setupCardReader(void);
        
        /*
        function: readCardID()
        description: Reads for a card, and changes the current buffer with that caerd. 
        parameters: none
        returns: none
        */
        bool readCardID(void);
        
        /*
        function: returnCardID()
        description: returns the ID integer array of the card. 
        parameters: none
        returns: integer[] array with card ID data from last card read. 
        */
        unsigned char *returnCardID(void);
        
        
        /*
        function: clearCardID()
        description: clears out the current card UUID information
        parameters: none
        returns: none
        */
        void clearCardID(void);

    private:
    
        // RFID manipulation object. 
        MFRC522 mfrc522 = MFRC522(SS_PIN, RST_PIN);
        // Card ID byte array. 
        uint8_t cardID[4] = {0, 0, 0, 0};
};

#endif