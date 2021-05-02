/*
Name: Charlie Chen, Ryan Brooks
ID: 1530605
Course: CKPUT 274 fall 2018
assignment: Assignment 2 part 2: encryped arduino communication
                                 xomplete implementation
*/

// include the arduino header file and
// the powmod header file
// the powmod header defines all the
// functions that allow powmod to work
#include <Arduino.h>  // angle brackets, from the system
#include "powmod.h"  // look in the local directory first

const int idpin = 13;
const int randpin = 1;

/*
Reads everything in the Serial3 buffer and discards it.
*/
void clearbuffer() {
    while (Serial3.available() > 0)
        Serial3.read();
}
// The setup function runs init and begins the
// serial ports
void setup() {
    init();
    Serial.begin(9600);
    Serial3.begin(9600);
}


// This function creates the private key
// for later use in creating a public key
// and a shared public key
uint32_t myPrivateKey() {
    uint32_t LSB;
    uint32_t result = 0;
    for (int i = 0; i < 32; i++) {
        uint32_t value = analogRead(randpin);
        LSB = value & 1;
        result = result << 1;
        result = result | LSB;
        delay(50);
    }
    return result;
  }

  uint32_t mul_mod(uint32_t a, uint32_t b, uint32_t m) {
  uint32_t result = 0;  // variable to store the result
  uint32_t runningCount = b % m;  // holds the value of b*2^i

  for (int i = 0 ; i < 32 ; i++) {
    if (i > 0) runningCount = (runningCount << 1) % m;
    if (bitRead(a, i)) {
      result = (result%m + runningCount%m) % m;
    }
  }
  return result;
}
/*
    Compute and return (a to the power of b) mod m.
    Assumes 1 <= m < 2^16 (i.e. that m fits in a uint16_t).
    Example: powMod(2, 5, 13) should return 6.
*/
uint32_t powModFast(uint32_t a, uint32_t b, uint32_t m) {
    // compute ap[0] = a
    // ap[1] = ap[0]*ap[0]
    // ...
    // ap[i] = ap[i-1]*ap[i-1] (all mod m) for i >= 1

    uint32_t result = 1%m;
    uint32_t sqrVal = a%m;  // stores a^{2^i} values, initially 2^{2^0}
    uint32_t newB = b;

    // LOOP INVARIANT: statements that hold throughout a loop
    //                 with the goal of being convinced the loop works
    // statements: just before iteration i,
    //               result = a^{binary number represented
    //               the first i bits of b}
    //               sqrVal = a^{2^i}
    //               newB = b >> i
    while (newB > 0) {
        if (newB&1) {  // evalutates to true iff i'th bit of b is 1
            result = mul_mod(result, sqrVal, m);
        }
        sqrVal = mul_mod(sqrVal, sqrVal, m);
        newB = (newB>>1);
    }

    // upon termination: newB == 0
    // so b >> i is 0
    // so result a^{binary number represented the first i bits of b} = a^b,
    // DONE!

    // # iterations ~ log_2 b ~ # of bits to write b
    // running time = O(log b)
    // NOTATION: we write O(some function) to express how the running times
    //           grows as a function of the input

    return result;
}


// Taken from the diffie_hellman_prelim.cpp file provided on EClass
// This function creates both arduino's public keys and takes an input
// to create the shared private key for both arduino's to be able to
// communicate,  At the end the shared private key is returned to be used
// in encryption and decryption.
uint32_t diffieHellman(uint32_t myprivatekey) {
    const uint32_t p = 2147483647;
    const uint32_t g = 16807;

    uint32_t myPublicKey = powModFast(g, myprivatekey, p);
    return myPublicKey;
}

// function that creates a list of shared
// public keys
uint32_t sharedkey(uint32_t myprivatekey, uint32_t partnerkey) {
    const uint32_t p = 2147483647;
    uint32_t sharedSecretKey = powModFast(partnerkey, myprivatekey, p);
    return sharedSecretKey;
}





/** Waits for a certain number of bytes on Serial3 or timeout 
 * @param nbytes: the number of bytes we want
 * @param timeout: timeout period (ms); specifying a negative number
 *                turns off timeouts (the function waits indefinitely
 *                if timeouts are turned off).
 * @return True if the required number of bytes have arrived.
 */
bool wait_on_serial3(uint8_t nbytes, long timeout) {
  unsigned long deadline = millis() + timeout;  // wraparound not a problem
  while (Serial3.available() < nbytes && (timeout < 0 || millis() < deadline)) {
    delay(1);  // be nice, no busy loop
  }
  return Serial3.available() >= nbytes;
}

/** Writes an uint32_t to Serial3, starting from the least-significant
 * and finishing with the most significant byte. 
 */
void uint32_to_serial3(uint32_t num) {
  Serial3.write((char) (num >> 0));
  Serial3.write((char) (num >> 8));
  Serial3.write((char) (num >> 16));
  Serial3.write((char) (num >> 24));
}

/** Reads an uint32_t from Serial3, starting from the least-significant
 * and finishing with the most significant byte. 
 */
uint32_t uint32_from_serial3() {
  uint32_t num = 0;
  num = num | ((uint32_t) Serial3.read()) << 0;
  num = num | ((uint32_t) Serial3.read()) << 8;
  num = num | ((uint32_t) Serial3.read()) << 16;
  num = num | ((uint32_t) Serial3.read()) << 24;
  return num;
}


// function that waits for the client to send
// the acknowledgement before allowing data exchange
uint32_t waitforACK(char ACK, uint32_t ckey) {
    char AK = Serial3.read();
        if (AK == ACK) {
        Serial.println(AK);
        Serial.println();
            return ckey;
        } else {
            return waitforACK(ACK, ckey);
}
}


// This function performs the triple
// handshake for secure data exchange
uint32_t signals(char ACK, uint32_t skey) {
while (Serial3.available() == 0) {}
    char key = Serial3.read();
    Serial.println(key);
if (key == 'C') {
    if (wait_on_serial3(4, 1000) == true) {
        uint32_t ckey = uint32_from_serial3();
        Serial.println(ckey);
        clearbuffer();
        Serial3.write(ACK);
        // Serial3.flush();
        uint32_to_serial3(skey);
        // Serial3.flush();
        if (wait_on_serial3(1, 1000) == true) {
        ckey = waitforACK(ACK, ckey);
        Serial.print(ACK);
        Serial.println(ckey);
        return ckey;
        clearbuffer();

        // Timeout
        } else if (wait_on_serial3(1, 1000) == false) {
            return signals(ACK, skey);
        }
    // Timeout
    } else if (wait_on_serial3(4, 1000) == false) {
        return signals(ACK, skey);
    }
}
}

// this function works as the server
// for data exchange
uint32_t server(uint32_t myPublicKey) {
    char ACK = 'A';
    uint32_t skey = myPublicKey;
    uint32_t ckey = signals(ACK, skey);

    return ckey;
    }


// this function works as the client for
// data exchange
uint32_t client(uint32_t myPublicKey) {
    char CR = 'C';
    uint32_t ckey = myPublicKey;
    // Continuously sends connection requests until the acknowledgment
    // is given by the server.
    while (Serial3.available() == 0) {
    Serial3.write(CR);
    // Serial3.flush();
    uint32_to_serial3(ckey);
    // Serial3.flush();
    }
    // Waits until there are 5 bytes in the buffer then tests for
    // an acknowledgement message.
    if (wait_on_serial3(5, 1000) == true) {
    char key = Serial3.read();
    if (key == 'A') {
        Serial.println(key);
        uint32_t skey = uint32_from_serial3();
        // Sends acknowledgement of the acknowlegdement.
        char ACK = 'A';
        Serial3.write(ACK);
        // Serial3.flush();
        clearbuffer();
        return skey;
    } else {
        return client(myPublicKey);
    }
    // Timeout
    } else if (wait_on_serial3(5, 1000) == false) {
        return client(myPublicKey);
    }
}



/** Implements the Park-Miller algorithm with 32 bit integer arithmetic 
 * @return ((current_key * 48271)) mod (2^31 - 1);
 * This is linear congruential generator, based on the multiplicative
 * group of integers modulo m = 2^31 - 1.
 * The generator has a long period and it is relatively efficient.
 * Most importantly, the generator's modulus is not a power of two
 * (as is for the built-in rng),
 * hence the keys mod 2^{s} cannot be obtained
 * by using a key with s bits.
 * Based on:
 * http://www.firstpr.com.au/dsp/rand31/rand31-park-miller-carta.cc.txt
 */
uint32_t next_key(uint32_t current_key) {
  const uint32_t modulus = 0x7FFFFFFF;  // 2^31-1
  const uint32_t consta = 48271;  // we use that consta<2^16
  uint32_t lo = consta*(current_key & 0xFFFF);
  uint32_t hi = consta*(current_key >> 16);
  lo += (hi & 0x7FFF) << 16;
  lo += hi>>15;
  if (lo > modulus) lo -= modulus;
  return lo;
}

// chat function for data exchange
void chat(uint32_t sharedSecretKey) {
    // print some info about the key we are using
    uint32_t nextkey = next_key(sharedSecretKey);


    while (true) {
        if (Serial.available() > 0) {
            uint8_t c = Serial.read();


            // Serial.write() always writes a single byte, which the serial
            // monitor
            // interprets as a char (it interprets all bytes sent as chars)
            Serial.write(c);  // sends just one byte, the ASCII value of a
                              // character

            // encrypt using the secret key and display the encrypted byte
            // sharedSecretKey is 16 bits, but we cast it down to 8 bits to
            // encrypt

            // XOR operation taken from http://www.cplusplus.com/forum/articles/38516/
            int8_t encryptedChar = c ^ ((uint8_t) nextkey);
            uint32_t current_key =  nextkey;
            nextkey = next_key(current_key);

            Serial3.write(encryptedChar);
            Serial3.flush();
            }
            // decrypt and display the byte and the corresponding character
            // encryption and decryption are the same operation with an XOR
            // cipher!
        if (Serial3.available() > 0) {
            uint8_t encryptedChar1 = Serial3.read();
            uint8_t decryptedChar = encryptedChar1 ^ ((uint8_t) nextkey);
            uint32_t current_key =  nextkey;
            nextkey = next_key(current_key);
            Serial.write(decryptedChar);
            Serial.println();
            Serial.println();
            Serial3.flush();
            }
        }
    }


// main function
int main() {
    setup();
    int id = digitalRead(idpin);
    uint32_t myprivatekey = myPrivateKey();
    uint32_t myPublicKey = diffieHellman(myprivatekey);
    uint32_t partnerkey;


    if (id == HIGH) {
        partnerkey = server(myPublicKey);
    }

    if (id == LOW) {
        partnerkey = client(myPublicKey);
    }
    uint32_t sharedSecretKey = sharedkey(myprivatekey, partnerkey);

    clearbuffer();
    chat(sharedSecretKey);
    Serial.end();
    Serial3.end();
    return 0;
}
