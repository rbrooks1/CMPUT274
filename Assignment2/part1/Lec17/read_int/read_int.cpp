/*
	Simple program that reads a string from the serial monitor
	representing an integer and constructs the actual "int"
	using the 'atol()' library function.
	
	This is an example of reading characters into an array or 'buffer'.

    Learn about atol()
    https://www.tutorialspoint.com/c_standard_library/c_function_atol.htm
    
    Learn about Serial.available()
    https://www.arduino.cc/en/Serial/Available

    You will need to understand this file for Assign #2 Part 1
*/

#include <Arduino.h>
#include "read_int.h"

void setup() {
	init();
	Serial.begin(9600);
}

/*
	Given an array of characters str[] of length len.
	Reads character from the serial monitor until len-1 are
	read or '\r' is encountered and stores them sequentially in str[].
	Adds the null terminator to str[] at the end of this sequence.
*/
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
			}
			else {
				str[index] = byteRead;
				index += 1;
			}
		}
	}
	str[index] = '\0';
}

// read a string (of digits 0-9) from the serial monitor by reading
// characters until enter is pressed, and return an unsigned 32-bit 'int'
uint32_t readUnsigned32() {
	char str[32];
	readString(str, 32);
	return atol(str);
	// Tricky question: why does this work even when entering 4,000,000,000
	// which fits in an unsigned long but not a signed long (as atol returns)?
}

int main() {
	setup();

	while (true) {
		uint32_t number = readUnsigned32();

		Serial.print("I read integer: ");
		Serial.println(number);
        Serial.print(number, BIN);
        Serial.println();
	}

	/*
		Alternative to Serial.flush().
		Main difference: the serial port is no longer available, you have to call
		Serial.begin(9600) again if you want to use it. Useful if you want to use
		the TX0/RX0 pins for something else, but we never have to.
	*/
	Serial.end();

	return 0;
}
