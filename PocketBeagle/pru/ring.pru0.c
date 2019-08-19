/*
 *
 * Build and run with:
 * make -C /var/lib/cloud9/examples/extras/pru PRUN=pru0 TARGET=ring
 *
 * Makefile source at:
 * https://github.com/beagleboard/bone101/blob/gh-pages/examples/extras/pru/Makefile
 *
 */

#include <stdint.h>
#include <pru_cfg.h>
#include <pru_ctrl.h>
#include <stddef.h>
#include <rsc_types.h>

volatile register unsigned int __R30;
volatile register unsigned int __R31;

struct my_resource_table {
        struct resource_table base;
        uint32_t offset[1]; /* Should match 'num' in actual definition */
};

#pragma DATA_SECTION(pru_remoteproc_ResourceTable, ".resource_table")
#pragma RETAIN(pru_remoteproc_ResourceTable)
struct my_resource_table pru_remoteproc_ResourceTable = {
        1,      /* we're the first version that implements this */
        0,      /* number of entries in the table */
        0, 0,   /* reserved, must be zero */
        0,      /* offset[0] */
};

#pragma DATA_SECTION(init_pins, ".init_pins")
#pragma RETAIN(init_pins)
const char init_pins[] =  
	"/sys/devices/platform/ocp/ocp:P2_30_pinmux/state\0pruout\0" \
	"/sys/devices/platform/ocp/ocp:P2_32_pinmux/state\0pruin\0" \
	"\0\0";

void main(void) {
	/* Read GPIO input 2 and invert to GPIO output 3 */
        while(1) {
		if(__R31 & (1<<2))
			__R30 = 0;
		else
			__R30 = (1<<3);
        }
}
