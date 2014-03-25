/*
 * SPI_Helper.h
 *
 *  Created on: Mar 2, 2014
 *      Author: DC
 */

#ifndef SPI_HELPER_H_
#define SPI_HELPER_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/ssi.h"

#define SPI_CLOCK 8000000

void SPI_Init();


#endif /* SPI_HELPER_H_ */
