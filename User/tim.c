#include "tim.h"

void
TIM6_Init(void)
{
	//Enable the peripheral clock of the TIM6
	RCC->APB1ENR |= (0x1U << RCC_APB1ENR_TIM6EN_Pos);
	
	TIM6->ARR  = TIM_ARR - 1;                           //1 circule on reload
	TIM6->PSC  = PRESCALER - 1;
	
	TIM6->CR1 |= (0x1U << TIM_CR1_ARPE_Pos);           //Auto-reload preload enable 
	TIM6->CR2 |= (0x1U << TIM_CR2_MMS_Pos);
	
	TIM6->DIER |= (0x1U << TIM_DIER_UDE_Pos)
				     |  (0x1U << TIM_DIER_UIE_Pos);
	
	//TIM6->CR1 |= (0x1U << TIM_CR1_CEN_Pos);            //Counter enable
}
