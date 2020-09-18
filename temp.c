#include "temp.h"


void init(void)
{
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1 | SYSCTL_RCGCGPIO_R0 | SYSCTL_RCGCGPIO_R4 | SYSCTL_RCGCGPIO_R5 ;
    
    GPIO_PORTA_DIR_R |= (rs|en|fan|alarm);
    GPIO_PORTA_DEN_R |= (rs|en|fan|alarm);
    GPIO_PORTA_DATA_R &= ~(fan); 
    GPIO_PORTB_DIR_R |= 0XFF;
    GPIO_PORTB_DEN_R |= 0XFF;
    
    /* enable clocks */
    SYSCTL_RCGCADC_R |= 1;          /* enable clock to ADC0 */
    
    ADC0_ACTSS_R &= ~8;             /* disable SS3 during configuration */
    ADC0_EMUX_R &= ~0xF000;         /* software trigger conversion */
    ADC0_SSMUX3_R = 0;              /* get input from channel 0 */
    ADC0_SSCTL3_R |= 6;             /* take one sample at a time, set flag at 1st sample */
    ADC0_ACTSS_R |= 8;              /* enable ADC0 sequencer 3 */
 
    /* initialize PE3 for AIN0 input */
    GPIO_PORTE_AFSEL_R |= 8;        /* enable alternate function */
    GPIO_PORTE_DEN_R &= ~8;         /* disable digital function */
    GPIO_PORTE_AMSEL_R |= 8;        /* enable analog function */
 
    GPIO_PORTF_LOCK_R |= 0X4C4F434B;
    GPIO_PORTF_CR_R |= (sw1|sw2);
    GPIO_PORTF_DIR_R &= ~(sw1|sw2);
    GPIO_PORTF_DEN_R |= (sw1|sw2);
    GPIO_PORTF_PUR_R |= (sw1|sw2);
}

void delayUs(int num)
{
  for(int i=0 ; i < num *17 ; i++);
}
void delayMs1(int num)
{
  for(int i=0 ; i < num *17000 ; i++);
}

void LCD_command(unsigned char command)
{
    GPIO_PORTA_DATA_R &= ~(rs) ;     	/* RS = 0, R/W = 0 */
    GPIO_PORTB_DATA_R = command;
    GPIO_PORTA_DATA_R |= en;    	/* pulse E */
    delayUs(1);		/* Enable pulse Width */
    GPIO_PORTA_DATA_R &= ~(en);
    if (command < 4)
        delayMs1(2);         	/* command 1 and 2 needs up to 1.64ms */
    else
        delayUs(40);        /* all others 40 us */
}

void LCD_data(unsigned char data)
{
    GPIO_PORTA_DATA_R |= (rs);    /* RS = 1, R/W = 0 */
    GPIO_PORTB_DATA_R = data;
    GPIO_PORTA_DATA_R |= (en|rs);   /* pulse E */
    delayUs(1);
    GPIO_PORTA_DATA_R &= ~(en);
    delayUs(40);
    //LCD_command(0x06);      /* move cursor right */

}

  void LCD_start(void)
  {     
        delayMs1(20);            /* initialization sequence */// Wait >15 ms after power is applied
        LCD_command(0x30);		// command 0x30 = Wake up
        delayMs1(5);				// must wait 5ms, busy flag not available
        LCD_command(0x30);		// command 0x30 = Wake up #2
        delayUs(100);			// must wait 100us, busy flag not available
        LCD_command(0x30);		// command 0x30 = Wake up #3
        delayUs(100);			// must wait 100us, busy flag not available
        // Prepare LCD Operation and Function  
        LCD_command(0x38);      /* set 8-bit data, 2-line, 5x7 font */
        LCD_command(0x06);      /* move cursor right */
        LCD_command(0x01);      /* clear screen, move cursor to home */
        LCD_command(0x0F);      /* turn on display, cursor blinking */

  }

void inttochar (int n)
{
    char c[5];
    int f = 0;
    if (n == 0)
    {
      LCD_data('0');
      f = 1;
    }
    if (f == 0)
    {
        for(int i = 4 ; i>=0 ; i--)
        {
           c[i]= (n %10) + '0';
            n/=10;
        }  
        int beg = 0;
        for(int i = 0 ; i<5 ; i++)
        {
          if(c[i]!='0')
          {
            beg = i;
            break;
          }
        }
        for(int i = beg ; i<5 ; i++)
        {
          LCD_data(c[i]);
        }
    }
}

/* delay n milliseconds (16 MHz CPU clock) */
void delayMs2(int n)
{
    int32_t i, j;
    for(i = 0 ; i < n; i++)
        for(j = 0; j < 3180; j++);
}

