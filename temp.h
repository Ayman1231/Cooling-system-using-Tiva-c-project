#include "tm4c123gh6pm.h"
#include <stdint.h>
#include <stdio.h>


#define rs (1U << 2)
#define en (1U << 3)
#define alarm (1U << 6)
#define fan (1U << 7)

#define sw1 (1U << 4)
#define sw2 (1U )

void port_init(void);

void delayUs(int num);
void delayMs1(int num);
void LCD_command(unsigned char command);
void LCD_data(unsigned char data);
void LCD_start();
void inttochar (int n);

void delayMs2(int n);


