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
    D_8140E6EC = gTimerCounter / 3;
    D_8140E6F0 = gTimerCounter >> 1;
    D_8140E6F4 = gTimerShift6 & 1;
    D_8140E6F8 = gTimerShift5 & 1;
    D_8140E6FC = gTimerShift4 & 1;
    D_8140E700 = gTimerShift3 & 1;
    D_8140E704 = gTimerShift2 & 1;
    D_8140E708 = D_8140E6EC & 1;
    D_8140E70C = D_8140E6F0 & 1;
}

void Timer_Tick(void) {
    Timer_UpdateCounters();
}
