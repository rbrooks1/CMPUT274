#include <Arduino.h>

void setup() {
	init();
	Serial.begin(9600);
}

int main() {
	setup();

	// a value from -128 to 127
	int8_t byte = 123;

	// a value from 0 to 255
	uint8_t uByte = 255;

	// from -2^15 to 2^15-1
	int16_t anInt = -1234;

	// from 0 to 2^16-1
	uint16_t anUnsignedInt = 42345;

	// from -2^31 to 2^31-1
	int32_t aLong = 123456l; // the l at the end ensures this literal has type "long"

	// from 0 to 2^32-1
	uint32_t anUnsignedLong = 3000000000ul; // the ul at the end ensures this literal has type "unsigned long"

	for (int i = 0; i < 20; ++i) {
		uint32_t val = ((uint16_t)10000)*i;
		Serial.println(val);
	}

	Serial.println();
	int a = 0;
	Serial.println(a++);
	Serial.println(a);
	int b = 0;
	Serial.println(++b);
	Serial.println(b);


	Serial.end();
}
