/*
 * Oled.h
 *
 *  Created on: Sep 23, 2024
 *      Author: juan
 */

#ifndef OLED_H_
#define OLED_H_

//Oled
void OLED_send_command(uint8_t command);
void OLED_send_data(uint8_t data);
void OLED_init(void);
void OLED_Fill(uint8_t val);
void OLED_DrawChar(uint8_t x, uint8_t y, char c);
void OLED_DrawString(uint8_t x, uint8_t y, const char* str);
void OLED_info_dht11(uint8_t HI, uint8_t HD, uint8_t TI, uint8_t TD);


//debug
void Oled_intro();

#endif /* OLED_H_ */
