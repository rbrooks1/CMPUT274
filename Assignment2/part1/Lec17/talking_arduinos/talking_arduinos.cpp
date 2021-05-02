/*
	Talking arduinos example.
    This example shows you how to print to Serial (a.k.a Serial0)
    and Serial3.

    Learn about Arduino Serial functions:
    https://www.arduino.cc/en/Serial/Read

*/

#include <Arduino.h>

const int idPin = 8;

void setup() {
	init();
    // set idPin to INPUT and turn on the internal pullup resistor
	pinMode(idPin, INPUT);
    digitalWrite(idPin, HIGH);

	Serial.begin(9600);
	Serial3.begin(9600);
}

void sender() {
	Serial.println("I am Alice the sender");

	Serial3.println("hello Bob, this is Alice");
	Serial3.println("How are you?");
	Serial3.println("Do you want to chat?");
    Serial3.println(".");
}

void receiver() {
	Serial.println("I am Bob the receiver");

	// wait until some data has arrived
	while (true) {
		// wait until the sender has sent some data
		while (Serial3.available() == 0) { }
		char byteRead = Serial3.read();

		// the sender sends \r\n with println()
		// so we don't need to add our own \n
		Serial.print(byteRead);
	}
}

int main() {
	setup();

	if (digitalRead(idPin) == LOW) {
		sender();
	}
	else {
		receiver();
	}

	// TODO:
	// comment out the if/else part above
	// create your own unecrypted chat!
	// have an infinite loop (while (true)) that, in each iteration,
	// checks if something is available from Serial and print it
	// to Serial3, and also if something is available from Serial3
	// and print it to Serial

	Serial3.flush();
	Serial.flush();

	return 0;
}
