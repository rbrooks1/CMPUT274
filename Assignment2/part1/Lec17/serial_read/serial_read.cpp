#include <Arduino.h>
/*  This example shows you how to read characters from the keyboard
    and print them to the screen one character at a time using the
    UA serial-mon program.

    Learn about arduino:
        Serial.read() https://www.arduino.cc/en/Serial/Read 
        Serial.available()

    You can connect 2 Arduinos to one PC:
    1. Run arduino-port-select to config your ports
    2. use $ serial-mon | serial-mon-0 | serial-mon-1 for each Arduino

    CMPUT274 Fa18 Lecture 17 Having arduinos talk to each other
*/
const int idPin = 8;

void setup() {
	init();
    pinMode(idPin, INPUT);
    digitalWrite(idPin, HIGH);
	Serial.begin(9600);
}


int main() {
	setup();

    int pinRead = digitalRead(idPin);
    Serial.print("idPin8 is: ");
    Serial.println(pinRead);

	// loop forever
	while (true) {
        // wait until some data has arrived
		while (Serial.available() == 0) { }
		char byteRead = Serial.read();

		//TODO: after running the program once,
        // uncomment the HEX, DEC, BIN print format and
		// check the ascii table at www.asciitable.com
		// for each character you press on the keyboard.
        // Q1: Is #1 below different from #3?
        // Q2: #1 is an example of 'type casting'. What does that mean?
        //      hint: search 'c++ type casting'

        // check for CR i.e. '\r'
		if ((int) byteRead == 13) {
			Serial.println();
		}
		else {
			  Serial.print(byteRead);
//              Serial.println((int) byteRead); // #1
//              Serial.print(byteRead, HEX);    // #2
//              Serial.print(byteRead, DEC);    // #3
// 	            Serial.print(byteRead, BIN);    // #4

		}
	}

	Serial.flush();

	return 0;
}
