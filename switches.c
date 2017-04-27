/*
 * switches.c

 *
 *  Created on: Sep 7, 2016
 *      Author: hornej2
 */

#include "switches.h"
#include "xil_io.h"
#include "xparameters.h"
#include <stdio.h>
#include "supportFiles/leds.h"

#define SWITCHES_GPIO_DEVICE_BASE_ADDRESS XPAR_SLIDE_SWITCHES_BASEADDR
#define GPIO_DATA_OFFSET 0x0
#define GPIO_TRI_OFFSET 0x4
#define GPIO_VALUE 0xf
#define LEDS_OFF 0x0

//write to the register
int32_t switches_readGpioRegister(int32_t offset){
    return Xil_In32(SWITCHES_GPIO_DEVICE_BASE_ADDRESS + offset);
}

//read from the register
void switches_writeGpioRegister(int32_t offset){
    return Xil_Out32(SWITCHES_GPIO_DEVICE_BASE_ADDRESS + offset,GPIO_VALUE);
}

// Initializes the SWITCHES driver software and hardware. Returns one of the STATUS values defined above.
int32_t switches_init(){
    switches_writeGpioRegister(GPIO_TRI_OFFSET);
    return SWITCHES_INIT_STATUS_OK;
}

// Returns the current value of all 4 SWITCHESs as the lower 4 bits of the returned value.
// bit3 = SW3, bit2 = SW2, bit1 = SW1, bit0 = SW0.
int32_t switches_read(){
    switches_readGpioRegister(GPIO_DATA_OFFSET);
}

// Runs a test of the switches. As you slide the switches, LEDs directly above the switches will illuminate.
// The test will run until all switches are slid upwards. When all 4 slide switches are slid upward,
// this function will return.
void switches_runTest(){
    switches_init();
    leds_init(true);
    while(switches_read()!=GPIO_VALUE){ //this will run until all switches are up
       leds_write(switches_read()); //takes what is read and writes it to the leds
    }
leds_write(LEDS_OFF); //turns all leds off
}
