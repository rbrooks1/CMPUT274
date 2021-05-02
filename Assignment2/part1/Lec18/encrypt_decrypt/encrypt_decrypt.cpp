/*
	A simple example of encrypting a character read from the serial monitor
	and then decrypting it again using a fixed "secret key".
*/

#include <Arduino.h>

void setup() {
	init();
	Serial.begin(9600);
}

/*
	You will replace this function by the Diffie-Hellman protocol for
	assignment 2. For now, just return some fixed secret key.
*/
uint32_t getSharedSecretKey() {
	return 8675309ul;
}

/*
	The main chat program. Will encrypt and decrypt messages using a given key.
	For now, this just reads characters from the serial monitor, encrypts them,
	and then decrypts them on a single Arduino.

	You have to replace this with two talking Arduinos, 
    and add the encryption/decryption to these Arduinos.
*/
void chat(uint32_t sharedSecretKey) {
	// print some info about the key we are using
	Serial.print("Encrypting with key: ");
	Serial.println(sharedSecretKey);
	Serial.print("When cast to a single byte: ");
	Serial.println((uint8_t) sharedSecretKey);
	Serial.println();


	while (true) {
		if (Serial.available() > 0) {
			uint8_t c = Serial.read();

			Serial.print("Received character: ");
			// Serial.write() always writes a single byte, which the serial monitor
			// interprets as a char (it interprets all bytes sent as chars)
			Serial.write(c); // sends just one byte, the ASCII value of a character
			Serial.println();
			Serial.print("ASCII value (byte): ");
			Serial.println(c);

			// encrypt using the secret key and display the encrypted byte
			// sharedSecretKey is 16 bits, but we cast it down to 8 bits to encrypt
			uint8_t encryptedChar = c ^ ((uint8_t) sharedSecretKey);
			Serial.print("Encrypted byte (ASCII): ");
			Serial.println(encryptedChar);

			// you can uncomment the following to see what it does,
			// but the characters may not be printable
			// Serial.print("The encrypted character: ");
			// Serial.write(encryptedChar);
			// Serial.println();

			// decrypt and display the byte and the corresponding character
			// encryption and decryption are the same operation with an XOR cipher!
			uint8_t decryptedChar = encryptedChar ^ ((uint8_t) sharedSecretKey);
			Serial.print("Decrypted byte: ");
			Serial.println(decryptedChar);
			Serial.print("Decrypted character: ");
			Serial.write(decryptedChar);
			Serial.println();

			Serial.println();
		}
	}
}

int main() {
	setup();

	uint32_t sharedSecretKey = getSharedSecretKey();

	chat(sharedSecretKey);

	// We won't reach this line as chat() has an infinite loop that never breaks,
	// but it's here for emphasis.
	Serial.end();

	return 0;
}
