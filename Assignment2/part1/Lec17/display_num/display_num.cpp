/*
	In this experiment decimal number from 0 to 63 (2^6 - 1) 
	is read from Serial0 converted to int, and then displayed in binary
	on 5 LEDs. 

*/

#include <Arduino.h>
#include "read_int.h"

// globally defined number of LEDs, and BINary n-bit position 2^n
#define NUM_LEDS 5
#define BIN_1 0
#define BIN_2 1
#define BIN_4 2
#define BIN_8 3
#define BIN_16 4


// must have this function to initialize things
void setup( const int pins[] ) {
	init();

	// Must initialize serial port communications before using Serial.
	Serial.begin(9600);

	// initialize pins
    for (int i = 0; i < NUM_LEDS; ++i) {
        pinMode( pins[i], OUTPUT );
    }

}

//  Print number to Serial0 in both ascii DECimal and BINary
void prntNumSerial( uint32_t num ) {
        
        if (num == 26) {
            Serial.print( "I will meet U @: " );
		    Serial.print( num );
		    Serial.println( " at 14:30 this Friday" );
		    Serial.print( num, BIN );
		}
		else {
		    Serial.print( "I read an integer: " );
		    Serial.print( num );
		    Serial.print( " try again Bob" );
        }
        Serial.println();
}

//  Based on the states given in 'LEDs', set the pins to their
//  HIGH or LOW state.
void setLEDs( int LEDs[], const int pins[] ) {
    for (int i = 0; i < NUM_LEDS; ++i) {
        digitalWrite( pins[i], LEDs[i] );
    }
}

//  Update the state of the display's LEDs by converting number from decimal
//  to binary represention stored in LEDs[]
void updateLEDs( uint32_t num, int LEDs[] ) {
    //set all LEDStates to LOW
    for (int i = 0; i < NUM_LEDS; ++i) {
        LEDs[i] = LOW;
    }
    // TODO ASCII table partial implementation
    switch(num) {
        case 0 :
            LEDs[BIN_1] = LOW;
            break;
        case 1 :
            LEDs[BIN_1] = HIGH;
            break;
        case 2 :
            LEDs[BIN_2] = HIGH;
            break;
        case 3 :
            LEDs[BIN_1] = HIGH;
            LEDs[BIN_2] = HIGH;
            break;
        case 4 :
            LEDs[BIN_4] = HIGH;
            break;
        case 5 :
            LEDs[BIN_4] = HIGH;
            LEDs[BIN_1] = HIGH;
            break;
        case 6 :
            LEDs[BIN_4] = HIGH;
            LEDs[BIN_2] = HIGH;
            break;
        case 7 :
            LEDs[BIN_4] = HIGH;
            LEDs[BIN_2] = HIGH;
            LEDs[BIN_1] = HIGH;
            break;
        case 8 :
            LEDs[BIN_8] = HIGH;
            break;
        case 26 :
            LEDs[BIN_2] = HIGH;
            LEDs[BIN_8] = HIGH;
            LEDs[BIN_16] = HIGH;
            break;
        default :
            Serial.println( "undefined display number" );
    }
}

// REQUIRED!
int main() {

	int LEDStates[] = {LOW, LOW, LOW, LOW, LOW};
    const int LEDPins[] = {9, 10, 11, 12, 13};	// same as Lab 2
	
	setup( LEDPins ); // our first act should be to initialize everything
	
// First draft of design broken down by program tasks/features
// TODO 1. read a str from serial-mon and convert to number (separate file)
//      TODO 1a read ascii numbers one-char-at-a-time into a string buffer
//      TODO 1b convert the numbers to unsigned integers
// TODO 2. print number, decimal & binary representations, to serial-mon
// TODO 3. display the binary representation on the 5 LEDs
//      TODO 3a update LEDs binary states to display DEC 0 - 31
//      TODO 3b set the LEDPins according to LEDStates

	while (true) {
        // 1. read a str from serial-mon and convert to integer
		uint32_t number = readUnsigned32();
		
		// 2. print number, decimal & binary representations, to serial-mon
		prntNumSerial( number );

        // TODO 3. display the binary representation on the 5 LEDs
        //      TODO: 3a update LEDs binary states to display DEC 0 - 31
        updateLEDs( number, LEDStates );    // unfinished
        
        // 3b set the LEDPins according to LEDStates
        setLEDs( LEDStates, LEDPins );
    }

	Serial.flush();

	return 0;
} // end main()
