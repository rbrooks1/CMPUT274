#include <Arduino.h>
#include "read_int.h"

// see read_int.h header file for function defintions
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

uint32_t readUnsigned32() {
	char str[32];
	readString(str, 32);
	return atol(str);
	// Tricky question: why does this work even when entering 4,000,000,000
	// which fits in an unsigned long but not a signed long (as atol returns)?
}
