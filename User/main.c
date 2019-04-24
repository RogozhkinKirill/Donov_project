#include "main.h"

void
Start(void)
{
	DAC->CR            |= (0x1U << DAC_CR_EN1_Pos);
	DMA1_Channel3->CCR |= (0x1U << DMA_CCR_EN_Pos);      
	TIM6->CR1          |= (0x1U << TIM_CR1_CEN_Pos);
}

int
main(void)
{
	DTR_Init();
	
	TIM6_Init();
	
	DAC_Init();
	
	//Start();
	
	while(1)
	{
		
	}
}
