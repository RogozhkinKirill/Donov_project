#include "dac.h"

void
DAC_Port_Init(void)
{
	//Enable the peripheral clock of the line PA
	RCC->APB1ENR |= RCC_AHBRSTR_GPIOARST;
	
	//PA4
	GPIOA->MODER   |= (0x3U << GPIO_MODER_MODER4_Pos); //Port mode analog
	GPIOA->OTYPER  |= (0x0U << GPIO_MODER_MODER4_Pos); //Output push/pull
	GPIOA->OSPEEDR |= (0x2U << GPIO_MODER_MODER4_Pos); //Medium speed
	GPIOA->PUPDR   |= (0x0U << GPIO_MODER_MODER4_Pos); //No pull-up, pull-down
}


void
DAC_DMA_Init(void)
{
	//Enable the peripheral clock of the DMA
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	
	DMA1_Channel3->CPAR  |= (uint32_t)(&(DAC1->DHR8R1));  //Base address of the peripheral data register to which the data will be written.
	DMA1_Channel3->CMAR   = (uint32_t)(Slava_bogu + 0);         //Base address of the memory area from which the data will be read.
	DMA1_Channel3->CNDTR |= 21000;                          //Number of data to be transferred (0 up to 65535)
	DMA1_Channel3->CCR   |= (0x1U << DMA_CCR_TCIE_Pos)     //Transfer complete interrupt enable
											 |  (0x1U << DMA_CCR_TEIE_Pos)     //Transfer error interrupt enable
											 |  (0x1U << DMA_CCR_DIR_Pos)			 //Read from memory
											 |  (0x1U << DMA_CCR_CIRC_Pos)     //Circule mode on
											 |  (0x0U << DMA_CCR_PINC_Pos)     //Periph incr off
											 |  (0x1U << DMA_CCR_MINC_Pos)     //Memory incr on
											 |  (0x0U << DMA_CCR_PSIZE_Pos)    //Periph size 8-bit
											 |  (0x0U << DMA_CCR_MSIZE_Pos)    //Memory size 8-bit
											 |  (0x1U << DMA_CCR_PL_Pos)       //Channel priority medium
											 |  (0x0U << DMA_CCR_MEM2MEM_Pos); //Mem to mem mode off
	//DMA1_Channel3->CCR   |= (0x1U << DMA_CCR_EN_Pos);      //DMA enable
	
	
	NVIC_SetPriority(DMA1_Channel2_3_IRQn, 1);
	NVIC_EnableIRQ(DMA1_Channel2_3_IRQn); 
}

void
DAC_Init(void)
{
	DAC_Port_Init();
	
	DAC_DMA_Init();
	
	//Enable the peripheral clock of the DAC
	RCC->APB1ENR |= RCC_APB1ENR_DACEN;
	
	DAC->CR |= (0x0U << DAC_CR_DMAUDRIE1_Pos)	         //DMA1 underrun interrupt enable
					|  (0x1U << DAC_CR_DMAEN1_Pos)		         //DMA enable
					|  (0x6U << DAC_CR_TSEL1_Pos)			         //Trigger by software
					|  (0x0U << DAC_CR_TEN1_Pos)			         //DAC trigger disable
					|  (0x0U << DAC_CR_BOFF1_Pos)     				 //DAC output buffer enable
					|	 (0x0U << DAC_CR_EN1_Pos);      				 //DAC disable
	
	//DAC->CR |= (0x1U << DAC_CR_EN1_Pos);
}
