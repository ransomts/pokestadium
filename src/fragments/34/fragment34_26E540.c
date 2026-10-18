#include "fragment34.h"

void Timer_UpdateCounters(void) {
    gTimerCounter++;
    gTimerMask6 = gTimerCounter & 0x3F;
    gTimerMask5 = gTimerCounter & 0x1F;
    gTimerMask4 = gTimerCounter & 0xF;
    gTimerMask3 = gTimerCounter & 7;
    gTimerMask2 = gTimerCounter & 3;
    gTimerMod3 = gTimerCounter % 3;
    gTimerMask1 = gTimerCounter & 1;
    gTimerShift6 = gTimerCounter >> 6;
    gTimerShift5 = gTimerCounter >> 5;
    gTimerShift4 = gTimerCounter >> 4;
    gTimerShift3 = gTimerCounter >> 3;
    gTimerShift2 = gTimerCounter >> 2;
    gTimerDiv3 = gTimerCounter / 3;
    gTimerShift1 = gTimerCounter >> 1;
    gTimerBit6 = gTimerShift6 & 1;
    gTimerBit5 = gTimerShift5 & 1;
    gTimerBit4 = gTimerShift4 & 1;
    gTimerBit3 = gTimerShift3 & 1;
    gTimerBit2 = gTimerShift2 & 1;
    gTimerDiv3Parity = gTimerDiv3 & 1;
    gTimerBit1 = gTimerShift1 & 1;
}

void Timer_Tick(void) {
    Timer_UpdateCounters();
}
