#include "mov_detector.h"

void 
EXTI2_3_IRQHandler(void)
{
	if(EXTI->PR & (0x1U << EXTI_PR_PR3_Pos) )
	{
		static uint8_t i = 0;
		//Reset Pending register
		EXTI->PR |= (0x1U << EXTI_PR_PR3_Pos);
		
		if(!i)
		{
			DAC->CR            |= (0x1U << DAC_CR_EN1_Pos);
			DMA1_Channel3->CCR |= (0x1U << DMA_CCR_EN_Pos);      
			TIM6->CR1          |= (0x1U << TIM_CR1_CEN_Pos);
			i++;
		}
		/*else
		{
			i--;
			DAC->CR            &= ~(0x1U << DAC_CR_EN1_Pos);
			DMA1_Channel3->CCR &= ~(0x1U << DMA_CCR_EN_Pos);      
			TIM6->CR1          &= ~(0x1U << TIM_CR1_CEN_Pos);
		}*/
	}
}

void
DTR_Port_Init(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; 
	
	//PA3
	GPIOA->MODER   |= (0x0U << GPIO_MODER_MODER3_Pos); //Port mode Input function
	GPIOA->OTYPER  |= (0x0U << GPIO_MODER_MODER3_Pos); //Output push/pull
	GPIOA->OSPEEDR |= (0x2U << GPIO_MODER_MODER3_Pos); //Medium speed
	GPIOA->PUPDR   |= (0x2U << GPIO_MODER_MODER3_Pos); //pull-down

	
	SYSCFG->EXTICR[0] |= (uint16_t)(0x0U << SYSCFG_EXTICR1_EXTI3_Pos); //Select input port PA3 for external interrupt.  
}


void 
DTR_Init(void)
{
	DTR_Port_Init();

	EXTI->IMR  |= (0x1U << EXTI_IMR_MR3_Pos); 
	EXTI->RTSR |= (0x1U << EXTI_RTSR_TR3_Pos);  //Rising Trigger
	EXTI->FTSR |= (0x0U << EXTI_FTSR_TR3_Pos);  //Falling Trigger
	
	
	/* Configure NVIC for External Interrupt */
	NVIC_SetPriority(EXTI2_3_IRQn,0); 
	NVIC_EnableIRQ(EXTI2_3_IRQn); 
}
