#include "cardReader.h"

/*
function: setupCardReader()
description:initializes the card reader, and card reader spi settings
parameters: none
returns: none
*/
void rfidReader::setupCardReader(void){
    //sets the card ID to zero. 
    cardID[0] = 0;
    cardID[1] = 0;
    cardID[2] = 0;
    cardID[3] = 0;
    mfrc522.setSPIConfig();//configures SPI settings. 
    mfrc522.PCD_Init();        // Init MFRC522 card
    delay(500);//delays the whole program. 
}

/*
function: readCardID()
description: Reads for a card, and changes the current buffer with that caerd. 
parameters: none
returns: none
*/
bool rfidReader::readCardID(void){
    MFRC522::MIFARE_Key key;
    for (byte i = 0; i < 6; i++) {
            key.keyByte[i] = 0xFF;
    }
    // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
            return false ;
    }

    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial()) {
            return false;
    }
    //puts the byte array data in the card
    cardID[0] = mfrc522.uid.uidByte[0];
    cardID[1] = mfrc522.uid.uidByte[1];
    cardID[2] = mfrc522.uid.uidByte[2];
    cardID[3] = mfrc522.uid.uidByte[3];
    
    // Halt PICC
    bool cardMatch = false; 
    if(cardID[0] == 228 && cardID[1] == 60 && cardID[2] == 38 && cardID[3] == 235){
        cardMatch = true; 
    }
    mfrc522.PICC_HaltA();
    // Stop encryption on PCD
    mfrc522.PCD_StopCrypto1();
    
    // Return boolean status that tells us if our card matched. 
    return cardMatch;
}

/*
function: returnCardID()
description: returns the ID integer array of the card. 
parameters: none
returns: integer[] array with card ID data from last card read. 
*/
uint8_t* rfidReader::returnCardID(){
    return this->cardID;
}

/*
function: clearCardID()
description: clears out the current card UUID information
parameters: none
returns: none
*/
void rfidReader::clearCardID(void){
    cardID[0] = 0;
    cardID[1] = 0;
    cardID[2] = 0;
    cardID[3] = 0;
}
