/*
Name: Ryan Brooks
ID: 1530605
Course: CKPUT 274 fall 2018
assignment: Weekly exercise 5: counting lights
*/

#include <Arduino.h>
// assistance for the increment function and setup was given through
// https://forum.arduino.cc/index.php?topic=347453.0
// thank you to Dwightthinker
// initialization of the global variables to be used.
// including the LED's the increment/decrement button
// and a pointer value k


int LEDpins[5] = {9, 10, 11, 12, 13};

int iButtonPin = 6;

int iButtonVal;

int dButtonPin = 7;

int dButtonVal;

int k;


// setup to set the LEDpin values to start off and
// sets the LED's set as outputs
// also sets the buttons as inputs
void setup() {
    init();
    Serial.begin(9600);
    for (int i = 0; i < 5; i++) {
        pinMode(LEDpins[i], OUTPUT);
        digitalWrite(LEDpins[i], LOW);
  }

  pinMode(iButtonPin, INPUT_PULLUP);
  pinMode(dButtonPin, INPUT_PULLUP);
}


// the increment function checks for the first LED that is
// turned off and turns it on.  Afterwards the function
// checks for all the LED's before the first light that was
// turned off and turns all prior lights off


void increment() {
    for (int i = 0; i < 5; i++) {
         k = 0;
         if (digitalRead(LEDpins[i]) == LOW) {
            digitalWrite(LEDpins[i], HIGH);
            break;
        }
         k = k + 1;
         digitalWrite(LEDpins[i], LOW);
    }
    for (int j = k; j > 1; j--) {
        if (digitalRead(LEDpins[j] == HIGH)) {
            digitalWrite(LEDpins[j], LOW);
        }
    }
     // this section stops the lights from incrementing if the
     // button is held down.


     delay(5);
     while (iButtonVal == LOW) {
         iButtonVal = digitalRead(iButtonPin);
    }
}


// the decrement function checks for the first pin that is lit up
// and turns it off.  it also then turns the other pins to high.
void decrement() {
        for (int i = 0; i < 5; i++) {
            if (digitalRead(LEDpins[i]) == HIGH) {
                digitalWrite(LEDpins[i], LOW);
                break;
        }
         digitalWrite(LEDpins[i], HIGH);
    }
    delay(5);
    while (dButtonVal == LOW) {
        dButtonVal = digitalRead(dButtonPin);
    }
}


// the main function runs an infinite loop that checks which button was pressed
// and then runs the appropriate function.
int main() {
    setup();
    while (true) {
        dButtonVal = digitalRead(dButtonPin);
        iButtonVal = digitalRead(iButtonPin);
        if (iButtonVal == LOW) {
            increment();
        }
        if (dButtonVal == LOW) {
            decrement();
        }
    }
    return 0;
}
