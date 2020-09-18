#include "temp.h"

int main()
{
  init();
  LCD_start();
  int temperature;
  while(1) {
      LCD_command(0x1);
      LCD_data('T');
      LCD_data('E');
      LCD_data('M');
      LCD_data('P');
      LCD_data(':');
      LCD_data(' ');
      LCD_data(' ');
    while(1)
    {  
        if(!(GPIO_PORTF_DATA_R & sw2))
        {
            LCD_command(0x1);
            LCD_data('P');
            LCD_data('O');
            LCD_data('W');
            LCD_data('E');
            LCD_data('R');
            LCD_data(' ');
            LCD_data('O');
            LCD_data('F');
            LCD_data('F');
            delayMs2(3000);
            break;
        }
        ADC0_PSSI_R |= 8;           /* start a conversion sequence 3 */
        while((ADC0_RIS_R & 0x08) == 0);                       /* wait for conversion to complete */
        temperature = ((ADC0_SSFIFO3_R * 330) / 4096);
        ADC0_ISC_R = 8;             /* clear completion flag */ 
        delayMs2(1000);
        if(temperature/10 > 0)
        {
            LCD_command(0x10);
        }
        LCD_command(0x10);
        inttochar(temperature);
     if(temperature > 40)
      {
         GPIO_PORTA_DATA_R |= (fan);
         int i = 0;
         for(i=0; i<9; i++)
         {
            if(!(GPIO_PORTF_DATA_R & sw2))
            {
                LCD_command(0x1);
                LCD_data('P');
                LCD_data('O');
                LCD_data('W');
                LCD_data('E');
                LCD_data('R');
                LCD_data(' ');
                LCD_data('O');
                LCD_data('F');
                LCD_data('F');
                delayMs2(3000);
                break;
            }
             ADC0_PSSI_R |= 8;           /* start a conversion sequence 3 */
             while((ADC0_RIS_R & 0x08) == 0);                       /* wait for conversion to complete */
             temperature = ((ADC0_SSFIFO3_R * 330) / 4096);
             ADC0_ISC_R = 8;             /* clear completion flag */ 
             delayMs2(1000);
             if(temperature < 40)
             {
               break;
             }
         }
         if(i==9)
         {
            GPIO_PORTA_DATA_R |= (alarm);
            delayMs2(3000);
            GPIO_PORTA_DATA_R &= ~(alarm);
            GPIO_PORTA_DATA_R &= ~(fan);
            break;
         }
      }   
      else {
         GPIO_PORTA_DATA_R &= ~(fan);
         GPIO_PORTA_DATA_R &= ~(alarm);
      }
    }
      LCD_command(0x1);
      LCD_data('F');
      LCD_data('O');
      LCD_data('R');
      LCD_data('C');
      LCD_data('E');
      LCD_data(' ');
      LCD_data('S');
      LCD_data('H');
      LCD_data('U');
      LCD_data('T');
      LCD_data('D');
      LCD_data('O');
      LCD_data('W');
      LCD_data('N');
      delayMs2(3000);  
      LCD_command(0x1);
    while (1)
    {
      if(!(GPIO_PORTF_DATA_R & sw1))
      {
          LCD_command(0x1);
          LCD_data('S');
          LCD_data('T');
          LCD_data('A');
          LCD_data('R');
          LCD_data('T');
          LCD_data('I');
          LCD_data('N');
          LCD_data('G');
          delayMs2(2000);
          break;
      }
    }
   }
  return 0;
}
