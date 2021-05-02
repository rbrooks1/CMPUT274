/*
Name: Charlie Chen, Ryan Brooks
ID: 1530605
Course: CKPUT 274 fall 2018
assignment: Assignment 2 part 1: encryped arduino communication
                                 simple proof of concept
*/
// include the arduino header file
#include <Arduino.h>

// initialize the analog pin to determine the random private key
const int randpin = 1;

// basic setup for initializing the serial ports
void setup() {
    init();
    Serial.begin(9600);
    Serial3.begin(9600);
    Serial.flush();
    Serial3.flush();
}

// This function runs a for loop 16 times to create a 16 bit
// random key based on fluctuating voltages in the 1st analog
// pin and returns it to be used in the creation of a public
// key.  The delay exists to help the voltage fluctuate more
// before the lesat significant bit of the voltage value
// is read and added to the start of the array.
uint16_t myPrivateKey() {
    uint16_t LSB;
    uint16_t result = 0;
    for (int i = 0; i < 16; i++) {
        uint16_t value = analogRead(randpin);
        LSB = value & 1;
        result = result << 1;
        result = result | LSB;
        delay(50);
    }

    return result;
}

// Taken from the diffie_hellman_prelim.cpp provided on the EClass page
uint32_t powMod(uint32_t g, uint32_t a, uint32_t p) {
    // multiply a by itself b times, keeping the intermediate
    // values mod m each step

    // question: if x,y are uint32_t, but each are < 2^16,
    // is (x*y) % m avoiding overflow?
    // YES: x*y < 2^32, so the multiplication does not overflow

    /*
        result = 1
        for b steps
            result = (result*a) mod m
        return result
    */

    g = g%p;
    uint32_t result = 1 % p;  // even initialize to be mod m
    for (uint32_t i = 0; i < a; i++) {
        result = (result*g) % p;
    }
    return result;
}

// Taken from the read_int.cpp provided on the EClass page.
// This function reads a string from the terminal to create a
// shard private key,  The reason for this function is that
// more than one byte needs to be read and serial.read() only
// reads one byte and ignores the rest.
void readString(char str[], int len) {
    // we didn't use a 'for' loop because we need the value of 'index' when
    // 'while' exits, so that we know where to add the null terminator '\0'

    int index = 0;
    while (index < len - 1) {
        // if something is waiting to be read on Serial0
        if (Serial.available() > 0) {
            char byteRead = Serial.read();
            // did the user press enter?
            if (byteRead == '\r') {
                break;
            } else {
                str[index] = byteRead;
                index += 1;
            }
        }
    }
    str[index] = '\0';
}

// read a string (of digits 0-9) from the serial monitor by reading
// characters until enter is pressed, and return an unsigned 32-bit 'int'
uint16_t otherPublicKey() {
    char str[16];
    readString(str, 16);
    return atol(str);
    // Tricky question: why does this work even when entering 4,000,000,000
    // which fits in an unsigned long but not a signed long (as atol returns)?
}

// Taken from the diffie_hellman_prelim.cpp file provided on EClass
// This function creates both arduino's public keys and takes an input
// to create the shared private key for both arduino's to be able to
// communicate,  At the end the shared private key is returned to be used
// in encryption and decryption.
uint32_t diffieHellman() {
    const uint32_t p = 19211;
    const uint32_t g = 6;
    uint16_t otherKey;

    // step 1 of setup procedure
    uint32_t myprivatekey = myPrivateKey();

    // step 2 of setup procedure
    uint32_t myPublicKey = powMod(g, myprivatekey, p);

    // step 3 of setup procedure
    Serial.print("My public key: ");
    Serial.print((myPublicKey), '\n');

    // step 4 of setup procedure
    Serial.flush();
    Serial.println("Enter partner's public key: ");
    // Assistance from TA Jason Cannon on making the arduino
    // wait for input.
    while (Serial.available() == 0) {}

    otherKey = otherPublicKey();  // should read from serial mon
    Serial.println("Partner's public key: ");
    Serial.println(otherKey);
    // step 5 of setup procedure
    uint32_t sharedSecretKey = powMod(otherKey, myprivatekey, p);

    return sharedSecretKey;
}


// Based on the encrypt_decrypt.cpp file provided on EClass
// This function runs a chat loop for encrypting and decrypting
// bits and bytes of text.  One arduino enters a line of text
// and it gets encrypted and sent to serial3 for the other arduino
// to decrypt and print to its own terminal.
void chat(uint32_t sharedKey) {
    // print some info about the key we are using
    Serial.print("Encrypting with key: ");
    Serial.println(sharedKey);
    Serial.print("When cast to a single byte: ");
    Serial.println((uint8_t) sharedKey);
    Serial.println();
    Serial3.flush();

    while (true) {
        if (Serial.available() > 0) {
            uint8_t c = Serial.read();

            Serial.print("Sent character: ");
            // Serial.write() always writes a single byte, which the serial
            // monitor
            // interprets as a char (it interprets all bytes sent as chars)
            Serial.write(c);  // sends just one byte, the ASCII value of a
                              // character
            Serial.println();
            Serial.print("ASCII value of sent character (byte): ");
            Serial.println(c);

            // encrypt using the secret key and display the encrypted byte
            // sharedSecretKey is 16 bits, but we cast it down to 8 bits to
            // encrypt

            // XOR operation taken from http://www.cplusplus.com/forum/articles/38516/
            int8_t encryptedChar = c ^ ((uint8_t) sharedKey);
            Serial.print("Encrypted byte (ASCII): ");
            Serial.println(encryptedChar);
            Serial3.write(encryptedChar);
            Serial3.flush();
            }
            // decrypt and display the byte and the corresponding character
            // encryption and decryption are the same operation with an XOR
            // cipher!
        if (Serial3.available() > 0) {
            uint8_t encryptedChar1 = Serial3.read();
            uint8_t decryptedChar = encryptedChar1 ^ ((uint8_t) sharedKey);
            Serial.print("Decrypted byte from partner: ");
            Serial.println(decryptedChar);
            Serial.print("Decrypted character: ");
            Serial.write(decryptedChar);
            Serial.println();
            Serial.println();
            Serial3.flush();
            }
        }
    }

// a main function to run all the other functions
// of the program.
int main() {
    setup();

    uint32_t sharedKey = diffieHellman();
    Serial.println("Shared Key: ");
    Serial.println((sharedKey), '\n');
    // begin chat
    chat(sharedKey);
    Serial.end();

    Serial3.flush();
    Serial.flush();
    return 0;
}
