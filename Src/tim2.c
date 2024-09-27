/*
 * Tim2_Bare_Metal_Custom_Lib.c
 *
 *  Created on: Sep 23, 2024
 *      Author: juan
 */
#include "stm32f1xx.h"
#include <stdint.h>

//timer
#define tim2_psc 72

//timer
uint8_t flag = 0;

void RCC_setup(void)
{
    // Habilitar o HSE (High-Speed External Clock)
    RCC->CR |= RCC_CR_HSEON;  // Liga o HSE
    while (!(RCC->CR & RCC_CR_HSERDY));  // Aguarda até que o HSE esteja pronto

    // Configurar o PLL para usar o HSE como fonte e multiplicar por 9
    RCC->CFGR &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL); // Limpar as configurações de PLL
    RCC->CFGR |= ( (1 << 16) | RCC_CFGR_PLLMULL9); // Configurar PLL com HSE e multiplicação por 9

    // Ligar o PLL
    RCC->CR |= RCC_CR_PLLON;  // Habilitar o PLL
    while (!(RCC->CR & RCC_CR_PLLRDY));  // Esperar o PLL ficar pronto

    // Configurar os divisores AHB, APB1 e APB2
    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;   // Sem divisão para o AHB (HCLK = SYSCLK)
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;  // Divisor 2 para APB1 (PCLK1 = HCLK/2)
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;  // Sem divisão para APB2 (PCLK2 = HCLK)

    // Configurar o Flash latency
    FLASH->ACR |= FLASH_ACR_LATENCY_2;  // 2 ciclos de espera para 72 MHz

    // Selecionar o PLL como a fonte do SYSCLK
    RCC->CFGR &= ~RCC_CFGR_SW;  // Limpar bits de seleção do SYSCLK
    RCC->CFGR |= RCC_CFGR_SW_PLL;  // Selecionar o PLL como a fonte de clock

    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);  // Esperar a transição para PLL

    // Desabilitar o HSI (opcional, se não for mais usado)
    RCC->CR &= ~RCC_CR_HSION;
}



void TIM2_setup(){

	// Enable clock access to timer2
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	// Configure timer2
	TIM2->PSC = tim2_psc - 1; 	//8000000/8 =100000 i.e. 1us
	TIM2->ARR = 1 - 1 ;


	/* Set UIE(Update interrupt enable) bit
	 * in TIMx DMA/Interrupt enable register (TIMx_DIER)
	 * to enable timer interrupt*/
	TIM2->DIER |= TIM_DIER_UIE;

	// Enable timer2 interrupt in NVIC
	NVIC_EnableIRQ(TIM2_IRQn);


}

void TIM2_delay_ms(uint32_t ms){

	while(ms--){
		TIM2_delay_us(1000);

	};

}

void TIM2_delay_us(uint32_t us){

	// Disable the timer
	TIM2->CR1 &= ~TIM_CR1_CEN;

	TIM2->ARR = us -1;

	// Enable the timer
	TIM2->CR1 |= TIM_CR1_CEN;

	while(!flag);
	flag = 0;

}



void TIM2_start_stop(uint8_t flag){

	if(flag){
		// Enable the timer
		TIM2->CR1 |= TIM_CR1_CEN;
	}else{
		// Disable the timer
		TIM2->CR1 &= ~TIM_CR1_CEN;
	}
}
/*
 * TIM2interrupt handler
 */
void TIM2_IRQHandler(void)
{
	if(TIM2->SR & TIM_SR_UIF)
	{
		TIM2->SR &=~TIM_SR_UIF;
		flag = 1;
		GPIOB->ODR ^= (1 << 11);

		TIM2->CR1 &= ~TIM_CR1_CEN;

	}

}
