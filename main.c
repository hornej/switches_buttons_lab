/*
 * main.c
 *
 *  Created on: Sep 7, 2016
 *      Author: hornej2
 */

#include "stdio.h"
#include "switches.h"
#include "buttons.h"
#include "supportFiles/leds.h"
#include "supportFiles/display.h"

int main() {
    switches_runTest();
    buttons_runTest();
}

void isr_function() {
    // Empty for now.
}
