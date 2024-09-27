/*
 * Tim2_Bare_Metal_Custom_Lib.h
 *
 *  Created on: Sep 23, 2024
 *      Author: juan
 */

#ifndef TIM2_H_
#define TIM2_H_

void RCC_setup(void);

//tim2
void TIM2_setup();

void TIM2_start_stop(uint8_t flag);

void TIM2_delay_us(uint32_t us);

void TIM2_delay_ms(uint32_t ms);

void TIM2_IRQHandler(void);

#endif /* TIM2_BARE_METAL_CUSTOM_LIB_H_ */
