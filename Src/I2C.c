/*
 * I2C_Bare_Metal_Custom_Lib.c
 *
 *  Created on: Sep 23, 2024
 *      Author: juan
 */

#include <dht11.h>
#include <stdint.h>

#include "tim2.h"
#include "I2C.h"

#include "stm32f1xx.h"



#define OLED_ADDRESS  0x3C



void I2C1_setup(void) {

    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

    GPIOB->CRL &= ~(GPIO_CRL_MODE6 | GPIO_CRL_CNF6 | GPIO_CRL_MODE7 | GPIO_CRL_CNF7);  // Limpa os bits
    GPIOB->CRL |= (GPIO_CRL_MODE6_1 | GPIO_CRL_CNF6_1 | GPIO_CRL_CNF6_0); // AF open-drain e 10MHz
    GPIOB->CRL |= (GPIO_CRL_MODE7_1 | GPIO_CRL_CNF7_1 | GPIO_CRL_CNF7_0); // AF open-drain e 10MHz

    // Configurar o clock I2C1 (APB1 é 36 MHz)
    I2C1->CR2 = 36;  // 36 MHz de clock periférico
    I2C1->CCR = 180;
    I2C1->TRISE = 37;

    // Habilitar o I2C1
    I2C1->CR1 |= I2C_CR1_PE;
}

void I2C1_start(void) {

    I2C1->CR1 |= I2C_CR1_START;
    //uart_write("I2C start!\n\r");


    while (!(I2C1->SR1 & I2C_SR1_SB));
    (void)I2C1->SR1; // Ler o registro SR1 para limpar o bit SB

}

void I2C1_stop(void) {
    // Gerar condição de stop
    I2C1->CR1 |= I2C_CR1_STOP;
    //uart_write("I2C stop!\n\r");
}

void I2C1_write(uint8_t data) {

    // Escrever o dado no DR
    I2C1->DR = data;
    // Esperar até que o dado seja transmitido
    while (!(I2C1->SR1 & I2C_SR1_TXE));
    //uart_write("I2C - write pong!\n\r");
    (void)I2C1->SR2;

}
