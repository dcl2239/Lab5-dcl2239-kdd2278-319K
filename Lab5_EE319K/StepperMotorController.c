// StepperMotorController.c starter file EE319K Lab 5
// Runs on TM4C123
// Finite state machine to operate a stepper motor.  
// Jonathan Valvano
// January 18, 2019

// Hardware connections (External: two input buttons and four outputs to stepper motor)
//  PA5 is Wash input  (1 means pressed, 0 means not pressed)
//  PA4 is Wiper input  (1 means pressed, 0 means not pressed)
//  PE5 is Water pump output (toggle means washing)
//  PE4-0 are stepper motor outputs 
//  PF1 PF2 or PF3 control the LED on Launchpad used as a heartbeat
//  PB6 is LED output (1 activates external LED on protoboard)

#include "SysTick.h"
#include "TExaS.h"
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

void EnableInterrupts(void);
// edit the following only if you need to move pins from PA4, PE3-0      
// logic analyzer on the real board
#define PA4       (*((volatile unsigned long *)0x40004040))
#define PE50      (*((volatile unsigned long *)0x400240FC))
#define SYSCTL_RCGCGPIO_R       (*((volatile uint32_t *)0x400FE608))
#define GPIO_PORTE_DIR_R        (*((volatile uint32_t *)0x40024400))
#define GPIO_PORTE_DEN_R        (*((volatile uint32_t *)0x4002451C))
#define GPIO_PORTE_DATA_R       (*((volatile uint32_t *)0x400243FC))

#define GPIO_PORTA_DATA_R       (*((volatile uint32_t *)0x400043FC))
#define GPIO_PORTA_DIR_R        (*((volatile uint32_t *)0x40004400))
#define GPIO_PORTA_DEN_R        (*((volatile uint32_t *)0x4000451C))
void SendDataToLogicAnalyzer(void){
  UART0_DR_R = 0x80|(PA4<<2)|PE50;
}

int main(void){ 
	int32_t mode = 0;
	TExaS_Init(&SendDataToLogicAnalyzer);    // activate logic analyzer and set system clock to 80 MHz
  SysTick_Init();   
// you initialize your system here
	SYSCTL_RCGCGPIO_R |= 0x12;
	SysTick_Wait(4);
	GPIO_PORTE_DIR_R &= 0x00;
	GPIO_PORTE_DIR_R |= 0x3F;
	GPIO_PORTE_DEN_R |= 0x3F;
	
	GPIO_PORTA_DIR_R &= 0x00;
	GPIO_PORTA_DEN_R &= 0x00;
	GPIO_PORTA_DEN_R |= 0x14;
	
	
  EnableInterrupts();   
  while(1){
// output
	if(mode == 1)
		{
			PE50 = 0x21; // wiper and pump
			SysTick_Wait10ms(5);
			PE50 = 0x02; 
			SysTick_Wait10ms(5);
	  	PE50 = 0x24; 
			SysTick_Wait10ms(5);
			PE50 = 0x08; 
			SysTick_Wait10ms(5);
			PE50 = 0x30; 
			SysTick_Wait10ms(5);
			PE50 = 0x21; // wiper and pump
			SysTick_Wait10ms(5);
			PE50 = 0x02; 
			SysTick_Wait10ms(5);
			PE50 = 0x24; 
			SysTick_Wait10ms(5);
			PE50 = 0x08; 
			SysTick_Wait10ms(5);
			PE50 = 0x30; 
			SysTick_Wait10ms(5);
			PE50 = 0x21; // wiper and pump
			SysTick_Wait10ms(5);
			
			
			
			
			PE50 = 0x21; 
			SysTick_Wait10ms(5);
			PE50 = 0x30;        //  reverse wiper
			SysTick_Wait10ms(5);
			PE50 = 0x08; 				
			SysTick_Wait10ms(5);
			PE50 = 0x24; 
			SysTick_Wait10ms(5);
			PE50 = 0x02; 
			SysTick_Wait10ms(5);
			PE50 = 0x21; 
			SysTick_Wait10ms(5);
			PE50 = 0x30;        //  reverse wiper
			SysTick_Wait10ms(5);
			PE50 = 0x08; 				
			SysTick_Wait10ms(5);
			PE50 = 0x24; 
			SysTick_Wait10ms(5);
			PE50 = 0x02; 
			SysTick_Wait10ms(5);
			PE50 = 0x21; 
			SysTick_Wait10ms(5);
			    //  reverse wiper
			
			
			
			
		}
	else if(mode == 2)
		{
		 PE50 = 0x01; // wiper 
			SysTick_Wait10ms(5);
			PE50 = 0x02; 
			SysTick_Wait10ms(5);
			PE50 = 0x04; 
			SysTick_Wait10ms(5);
			PE50 = 0x08; 
			SysTick_Wait10ms(5);
			PE50 = 0x10; 
			SysTick_Wait10ms(5);
			PE50 = 0x01; // wiper 
			SysTick_Wait10ms(5);
			PE50 = 0x02; 
			SysTick_Wait10ms(5);
			PE50 = 0x04; 
			SysTick_Wait10ms(5);
			PE50 = 0x08; 
			SysTick_Wait10ms(5);
			PE50 = 0x10; 
			SysTick_Wait10ms(5);
			PE50 = 0x01; // wiper 
			SysTick_Wait10ms(5);
			
			
			
			
			PE50 = 0x01; 
			SysTick_Wait10ms(5);
			PE50 = 0x10;        //  reverse wiper
			SysTick_Wait10ms(5);
			PE50 = 0x08; 				
			SysTick_Wait10ms(5);
			PE50 = 0x04; 
			SysTick_Wait10ms(5);
			PE50 = 0x02; 
			SysTick_Wait10ms(5);
			PE50 = 0x01; 
			SysTick_Wait10ms(5);
			PE50 = 0x10;        //  reverse wiper
			SysTick_Wait10ms(5);
			PE50 = 0x08; 				
			SysTick_Wait10ms(5);
			PE50 = 0x04; 
			SysTick_Wait10ms(5);
			PE50 = 0x02; 
			SysTick_Wait10ms(5);
			PE50 = 0x01; 
			SysTick_Wait10ms(5); 
		}
			
// wait
		
		
// input
		if(PA4 != 0)
		{
		mode = 1;  // wiper and pump
		}
		else if((GPIO_PORTA_DATA_R&0x04) != 0)
		{
		mode = 2; // wiper 
		}
		else
		{
		mode = 0;
		PE50 = 0x00; 
		}
		
		
		
		
// next		
  }
}


