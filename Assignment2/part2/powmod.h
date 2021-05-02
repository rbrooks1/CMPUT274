#ifndef _POWMOD_H_
#define _POWMOD_H_

// function declarations here
// the definitions (implementations) are in powmod.cpp

uint32_t powModSlow(uint32_t a, uint32_t b, uint32_t m);
uint32_t powModFast(uint32_t a, uint32_t b, uint32_t m);
void onePowModFastTest(uint32_t a, uint32_t b, uint32_t m, uint32_t expected);
void testPowModFast();

#endif
