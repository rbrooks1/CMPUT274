#ifndef _READINT_H_
#define _READINT_H_

// header file for some higher-level functions to read input from the serial monitor

/*
	Given an array of characters str[] of length len.
	Reads character from the serial monitor until len-1 are
	read or '\r' is encountered and stores them sequentially in str[].
	Adds the null terminator to str[] at the end of this sequence.
*/
void readString(char str[], int len);

// read a string (of digits 0-9) from the serial monitor by reading
// characters until enter is pressed, and return an unsigned 32-bit 'int'
uint32_t readUnsigned32();


#endif
