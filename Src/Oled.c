/*
 * Oled.c
 *
 *  Created on: Sep 23, 2024
 *      Author: juan
 */

#include "I2C.h"
#include "tim2.h"
#include "dht11.h"
#include "fonts.h"
#include "Usart1.h"

//I2C1
#define OLED_ADDRESS  0x3C
#define SSD1306_linha           64
#define SSD1306_coluna         128
#define OLED_PAGES  (SSD1306_coluna / 8)

//oled
uint8_t atual_x , atual_y= 0;

void OLED_send_command(uint8_t command) {
    // Iniciar a comunicação I2C
    I2C1_start();
    // Enviar o endereço do OLED e o bit de escrita
    //uart_write("I2C escrita start!\n\r");
    I2C1_write(OLED_ADDRESS << 1);
    //uart_write("I2C escrita start ok!\n\r");
    // Enviar o byte de controle para indicar que é um comando
    //uart_write("I2C cmd start!\n\r");
    I2C1_write(0x00);
    // Enviar o comando
    I2C1_write(command);
    // Parar a comunicação I2C
    I2C1_stop();
}

void OLED_send_data(uint8_t data) {
    // Iniciar a comunicação I2C
    I2C1_start();
    // Enviar o endereço do OLED e o bit de escrita
    I2C1_write(OLED_ADDRESS << 1);
    // Enviar o byte de controle para indicar que é dado
    I2C1_write(0x40);
    // Enviar o dado
    I2C1_write(data);
    // Parar a comunicação I2C
    I2C1_stop();
}

void OLED_init(void) {
    // Sequência de inicialização para o SSD1306
    OLED_send_command(0xAE); // Display OFF
    OLED_send_command(0x20); // Set Memory Addressing Mode
    OLED_send_command(0x10); // Set Page Addressing Mode
    OLED_send_command(0xB0); // Set Page Start Address for Page Addressing Mode
    OLED_send_command(0xC8); // Set COM Output Scan Direction
    OLED_send_command(0x00); // Set low column address
    OLED_send_command(0x10); // Set high column address
    OLED_send_command(0x40); // Set start line address
    OLED_send_command(0x81); // Set contrast control register
    OLED_send_command(0xFF); // Maximum contrast
    OLED_send_command(0xA1); // Set segment re-map 0 to 127
    OLED_send_command(0xA6); // Set normal display
    OLED_send_command(0xA8); // Set multiplex ratio (1 to 64)
    OLED_send_command(0x3F); // 1/64 duty
    OLED_send_command(0xA4); // Output RAM to display
    OLED_send_command(0xD3); // Set display offset
    OLED_send_command(0x00); // No offset
    OLED_send_command(0xD5); // Set display clock divide ratio/oscillator frequency
    OLED_send_command(0xF0); // Set divide ratio
    OLED_send_command(0xD9); // Set pre-charge period
    OLED_send_command(0x22);
    OLED_send_command(0xDA); // Set COM pins hardware configuration
    OLED_send_command(0x12);
    OLED_send_command(0xDB); // Set vcomh
    OLED_send_command(0x20); // 0.77x Vcc
    OLED_send_command(0x8D); // Set DC-DC enable
    OLED_send_command(0x14);
    OLED_send_command(0xAF); // Display ON
    uart_write("OLED set\n\r");
}

// Função para limpar o display OLED
void OLED_Fill(uint8_t val) {
	if(val > 0xff){
		uart_write("error, tamanho ecedido");
		return;
	}

    for (uint8_t page = 0; page < OLED_PAGES; page++) {
        // Configura o OLED para escrever em cada página
    	OLED_send_command(0xB0 + page);  // Seleciona a página (0 a 7)
    	OLED_send_command(0x00);         // Coluna baixa
    	OLED_send_command(0x10);         // Coluna alta

        // Envia 128 bytes de zeros (0x00) para limpar uma linha inteira
        for (uint8_t col = 0; col < SSD1306_coluna; col++) {
        	OLED_send_data(val);  // 0x00 representa uma linha de pixels "desligados"
        }
    }
}

void OLED_DrawChar(uint8_t x, uint8_t y, char c) {

    // Seleciona a página (linha de pixels de 8 bits de altura)
	OLED_send_command(0xB0 + (y / 8));       // Seleciona a página (Y dividido por 8)
	OLED_send_command(0x00 + (x & 0x0F));    // Coluna baixa
	OLED_send_command(0x10 + ((x >> 4) & 0x0F)); // Coluna alta

    for (int i = 0; i < 5; i++) {
    	OLED_send_data(font5x7[c - 32][i]);  // Envia os bytes da fonte
    }
    OLED_send_data(0x00);  // Espaçamento entre caracteres
}

void OLED_DrawString(uint8_t x, uint8_t y, const char* str) {
    while (*str) {
        OLED_DrawChar(x, y, *str++);
        x += 6;  // Cada caractere tem 5 pixels de largura, mais 1 pixel de espaço
        if (x + 6 >= SSD1306_coluna) {
            x = 0;     // Move para o início da próxima linha
            y += 8;    // Avança para a próxima página
        }
    }
    atual_x = x;
    atual_y = y;
}

void Oled_intro(){
    OLED_Fill(0x00);
    TIM2_delay_ms(100);
    OLED_Fill(0x01);
    TIM2_delay_ms(100);
    OLED_Fill(0x10);
    TIM2_delay_ms(100);
    OLED_Fill(0x00);
}

void OLED_info_dht11(uint8_t HI, uint8_t HD, uint8_t TI, uint8_t TD){

	uint8_t l = 10,h = 10;
	char buffer[20];

	int_to_string(HI,buffer);
	OLED_DrawString(l,h,buffer);

	OLED_DrawString(atual_x,atual_y,".");

	int_to_string(HD,buffer);
	OLED_DrawString(atual_x,atual_y,buffer);

	OLED_DrawString(atual_x,atual_y," % DE HUMIDADE");

	l = 10;
	h = 30;

	int_to_string(TI,buffer);
	OLED_DrawString(l,h,buffer);

	OLED_DrawString(atual_x,atual_y,".");

	int_to_string(TD,buffer);
	OLED_DrawString(atual_x,atual_y,buffer);

	OLED_DrawString(atual_x,atual_y," C ");


}
