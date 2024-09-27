/*
 * Usart1_Bare_Metal_Custom_Lib.c
 *
 *  Created on: Sep 23, 2024
 *      Author: juan
 */
#include <stdint.h>
#include "Usart1.h"
#include "stm32f1xx.h"

#define CPU_CLK_72m 	72000000

//usart
#define BaudRate	115200


//uart
char ch = '\000';
char buffer[20];
uint8_t  buffer_index = 0;


void USART1_setup(){

	/*UART1 Pin configuration*/
	//enable clock access to GPIOA
	RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;

	/*Configure PA9(TX) as output maximum speed to 50MHz
	 * and alternate output push-pull mode for USART1*/
	GPIOA->CRH &= 0xFFFFFF0F;
	GPIOA->CRH |= 0x000000B0;

	//Configure PA10(RX) as as input floating as following
	GPIOA->CRH &= 0xFFFFF0FF;
	GPIOA->CRH |= 0x00000400;

	/*USART1 configuration*/

	//enable clock access to USART1
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	//Enable receiver
	USART1->CR1 |= USART_CR1_RE | USART_CR1_TE;
	//Set Baud Rate
	USART1->BRR = ((CPU_CLK_72m + (BaudRate/2U))/BaudRate);
	//Enable RXNIE interrupt
	USART1->CR1|=USART_CR1_RXNEIE;
	//Enable USART1 interrupt in NVIC
	NVIC_EnableIRQ(USART1_IRQn);
	//Enable UART
	USART1->CR1 |= USART_CR1_UE;
}

void uart_write(char *ch)
{
	while(*ch)
	{
		//Make sure the transmit data register is empty
		while(!(USART1->SR & USART_SR_TXE)){}
		//Write to transmit data register
		USART1->DR	=  (*ch & 0xFF);
		ch++;
	}
}

void uart_info_dht11(uint8_t HI, uint8_t HD, uint8_t TI, uint8_t TD){

    int_to_string(TI,buffer);
    uart_write(buffer);
    uart_write(",");
    int_to_string(TD,buffer);
    uart_write(buffer);
    uart_write(" C e ");

    int_to_string(HI,buffer);
    uart_write(buffer);
    uart_write(",");
    int_to_string(HD,buffer);
    uart_write(buffer);
    uart_write(" %\r");

}


void USART1_IRQHandler(void)
{
    /* Verifica a origem da interrupção */
    if (USART1->SR & USART_SR_RXNE) /* Recebeu um caractere */
    {
        /* Lê o dado */
        ch = USART1->DR;
        uart_write(&ch);
        // Armazena o caractere no buffer
        if (buffer_index < sizeof(buffer) - 1)  // Certifica-se de não ultrapassar o tamanho do buffer
        {
            buffer[buffer_index++] = ch;

            // Verifica se o caractere recebido é o fim da string (ex: '\n' ou '\r')
            if (ch == '\n' || ch == '\r')
            {
                buffer[buffer_index - 1] = '\0';  // Substitui o terminador por NULL para formar a string

                ch = '\n';
                uart_write(&ch);


                buffer_index = 0;  // Reseta o índice para a próxima string




            }
        }
        else
        {
            // Buffer cheio, reiniciar para evitar estouro
            buffer_index = 0;
        }

    }
}

void int_to_string(uint8_t value, char *str) {
    int i = 0;

    // Processa cada dígito e coloca no array
    do {
        str[i++] = (value % 10) + '0';  // Extrai o último dígito e converte para char
        value /= 10;                    // Remove o dígito processado
    } while (value > 0);

    // Adiciona o terminador nulo
    str[i] = '\0';

    // Inverte a string, já que os dígitos foram colocados em ordem inversa
    for (int j = 0; j < i / 2; j++) {
        char temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
    }
}
