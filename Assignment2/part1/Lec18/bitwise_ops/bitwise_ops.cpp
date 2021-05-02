#include <Arduino.h>

void setup() {
	init();
	Serial.begin(9600);
}

// prints the number in binary and then ends the line
void printBinary(int16_t num) {
	// now print all bits in reverse order of position
	for (int i = 15; i >= 0; i--) {
		// print the bit at position i of num

		// shift to the right i bits, and then get the
		// least significant bit
		int bit = (num>>i)&1;
		Serial.print(bit);
	}
	Serial.println();
}

// given anumber, will convert it to its negative
// value but using the 2s complement procedure
void print2sComplement(int16_t n) {
	Serial.print("Negating: ");
	Serial.println(n);
	Serial.print("It is: ");

	int16_t nComp = ~n + 1;

	Serial.println(nComp);
	// should print -n
}

int main() {
	setup();

	// in binary, 25 is 0000000000011001
	int16_t num = 25;

	// check the least significant bit
	// 1 is stored as   0000000000000001
	Serial.println(num & 1);
	Serial.println();

	printBinary(num);
	printBinary(-1);
	printBinary(-5);
	Serial.println();

	// set the bit at position 2 of num to 1
	// desired number in binary is 0000000000011101

	// 1<<2 is 0000000000000100
	// num is  0000000000011001
	// so | is 0000000000011101
	num = num | (1<<2);
	Serial.println(num);


	// 1<<2 is 0000000000000100
	// num is  0000000000011101
	// so | is 0000000000011101
	num = num | (1<<2);
	Serial.println(num); // what will this print?
	Serial.println();

	print2sComplement(1);
	print2sComplement(0);
	print2sComplement(15);
	print2sComplement(-19);
	// 1<<15 is the least negative number
	print2sComplement(1<<15);

	Serial.println();

	for (int i = 0; i < 20; ++i) {
		Serial.println(analogRead(A1)&1);
		delay(50);
	}

	Serial.end();

	return 0;
}
