/*
 * Usart1_Bare_Metal_Custom_Lib.h
 *
 *  Created on: Sep 23, 2024
 *      Author: juan
 */

#ifndef USART1_H_
#define USART1_H_

void USART1_setup();

void uart_write(char *ch);

void int_to_string(uint8_t value, char *str);

void uart_info_dht11(uint8_t HI, uint8_t HD, uint8_t TI, uint8_t TD);

void USART1_IRQHandler(void);

#endif /* USART1_BARE_METAL_CUSTOM_LIB_H_ */
