/*
	Includes the code for the basic Diffie-Hellman key exchange protocol.
	Current version works for 16-bit primes only.
*/

#include <Arduino.h>

int analogPin = 1;
vector<int> v;

void setup() {
	init();
	Serial.begin(9600);
    pinMode(analogPin, INPUT);
}

/*
	Compute and return (a to the power of b) mod m.
 	Assumes 1 <= m < 2^16 (i.e. that m fits in a uint16_t).
	Example: powMod(2, 5, 13) should return 6.
*/
uint32_t powMod(uint32_t a, uint32_t b, uint32_t m) {
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

	a = a%m;
	uint32_t result = 1 % m; // even initialize to be mod m
	for (uint32_t i = 0; i < b; i++) {
		result = (result*a) % m;
	}
	return result;
}

/*
	Check if powMod(a, b, m) == result
*/
void onePowModTest(uint32_t a, uint32_t b, uint32_t m,
									 uint32_t expected) {
	uint32_t calculated = powMod(a, b, m);
	if (calculated != expected) {
		Serial.println("error in powMod test");
		Serial.print("expected: ");
		Serial.println(expected);
		Serial.print("got: ");
		Serial.println(calculated);
	}
}

void testPowMod() {
	Serial.println("starting tests");
	// run powMod through a series of tests
	onePowModTest(1, 1, 20, 1); //1^1 mod 20 == 1
	onePowModTest(5, 7, 37, 18);
	onePowModTest(5, 27, 37, 31);
	onePowModTest(3, 0, 18, 1);
	onePowModTest(2, 5, 13, 6);
	onePowModTest(1, 0, 1, 0);
	onePowModTest(123456, 123, 17, 8);
	Serial.println("tests done!");
}

int privatekey() {
    for (int i = 0; i < 16; i++) {
        int leastSigBit = analogRead(analogPin) & 1;
        delay(50);
    }
    
}

uint32_t diffieHellman() {
	const uint32_t p = 19211;
	const uint32_t g = 6;

	// TODO: get a random number
	// step 1 of setup procedure
	uint32_t myPrivateKey = privateKey();

	// step 2 of setup procedure
	uint32_t myPublicKey = powMod(g, myPrivateKey, p);

	// TODO: print the public key to the screen
	// step 3 of setup procedure

	// TODO: type in the other Arduino's public key
	// step 4 of setup procedure
	uint32_t otherPublicKey = 456; // should read from serial mon

	// step 5 of setup procedure
	uint32_t sharedSecretKey = powMod(otherPublicKey, myPrivateKey, p);

	return sharedSecretKey;
}

int main() {
	setup();

	testPowMod();

	uint32_t sharedKey = diffieHellman();

	// begin chat, make sure to encrypt!

	Serial.end();

	return 0;
}
