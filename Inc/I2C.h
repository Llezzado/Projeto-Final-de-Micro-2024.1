/*
 * I2C.h
 *
 *  Created on: Sep 23, 2024
 *      Author: juan
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>
// I2C1
void I2C1_setup(void);
void I2C1_start(void);
void I2C1_stop(void);
void I2C1_write(uint8_t data);

#endif /* I2C_BARE_METAL_CUSTOM_LIB_H_ */
