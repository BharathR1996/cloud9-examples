////////////////////////////////////////
//	inputR31.c
//	Reads input in P8_19 via the R31 register and blinks the USR3 LED
//	Wiring:	Wire a switch between P8_19 and 3.3V (P9_3 or P9_4)
//	Setup:	None
//	See:	prugpio.h to see which pins attach to R31
//	PRU:	pru1_1
////////////////////////////////////////
#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"
#include "prugpio.h"

volatile register unsigned int __R30;
volatile register unsigned int __R31;

void main(void) {
	uint32_t *gpio3 = (uint32_t *)GPIO3;

	/* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

	while(1) {
		if(__R31 & P8_19) {
            gpio3[GPIO_SETDATAOUT]   = USR3;      // Turn off LED
        } else
            gpio3[GPIO_CLEARDATAOUT] = USR3;      // Turn on LED
	}
	__halt();
}

// Turns off triggers
#pragma DATA_SECTION(init_pins, ".init_pins")
#pragma RETAIN(init_pins)
const char init_pins[] =  
	"/sys/class/leds/beaglebone:green:usr3/trigger\0none\0" \
	"\0\0";
