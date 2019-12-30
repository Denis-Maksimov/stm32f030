.cpu cortex-m3      /* ограничиваем ассемблер списком существующих инструкций */
.syntax unified
.arch armv7-m
.thumb
.section .vectors
.global __isr_vectors
__isr_vectors:
	.word   0x20005000 	/* начало стека в самом конце памяти, стек растет вниз */
	.word   start+1        	/* с прерывания сразу прыгаем в код на С */
	.word 	nmi_fault+1
	.word 	hard_fault+1
	.word 	memory_fault+1
	.word 	bus_fault+1
	.word 	usage_fault+1
	.word	0
	.word	0
	.word	0
	.word	0
	.word	SVC_Handler+1
	.word	DebugMon_Handler+1
	.word	0
	.word	PendSV_Handler+1
	.word	SysTick_Handler+1
	.word	WWDG_IRQHandler+1
	.word	PVD_IRQHandler+1
	.word	TAMPER_IRQHandler+1
	.word	RTC_IRQHandler+1
	.word	FLASH_IRQHandler+1
	.word	RCC_IRQHandler+1
	.word	EXTI0_IRQHandler+1
	.word	EXTI1_IRQHandler+1
	.word	EXTI2_IRQHandler+1
	.word	EXTI3_IRQHandler+1
	.word	EXTI4_IRQHandler+1
	.word	DMA1_Channel1_IRQHandler+1
	.word	DMA1_Channel2_IRQHandler+1
	.word	DMA1_Channel3_IRQHandler+1
	.word	DMA1_Channel4_IRQHandler+1
	.word	DMA1_Channel5_IRQHandler+1
	.word	DMA1_Channel6_IRQHandler+1
	.word	DMA1_Channel7_IRQHandler+1
	.word	ADC1_2_IRQHandler+1
	.word	USB_HP_CAN1_TX_IRQHandler+1
	.word	USB_LP_CAN1_RX0_IRQHandler+1
	.word	CAN1_RX1_IRQHandler+1
	.word	CAN1_SCE_IRQHandler+1
	.word	EXTI9_5_IRQHandler+1
	.word	TIM1_BRK_IRQHandler+1
	.word	TIM1_UP_IRQHandler+1
	.word	TIM1_TRG_COM_IRQHandler+1
	.word	TIM1_CC_IRQHandler+1
	.word	TIM2_IRQHandler+1
	.word	TIM3_IRQHandler+1
	.word	TIM4_IRQHandler+1
	.word	I2C1_EV_IRQHandler+1
	.word	I2C1_ER_IRQHandler+1
	.word	I2C2_EV_IRQHandler+1
	.word	I2C2_ER_IRQHandler+1
	.word	SPI1_IRQHandler+1
	.word	SPI2_IRQHandler+1
	.word	USART1_IRQHandler+1
	.word	USART2_IRQHandler+1
	.word	USART3_IRQHandler+1
	.word	EXTI15_10_IRQHandler+1
	.word	RTCAlarm_IRQHandler+1
	.word	USBWakeUp_IRQHandler+1
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0

.size __isr_vectors, . - __isr_vectors

// -----------------------------------------------
// --- Функция - затычка -------------------------
// -----------------------------------------------
.macro DEFAULT_HANDLER   handler_name		//
						//
    .align 1					//
    .thumb_func					//
    .weak    \handler_name			//
    .type    \handler_name, %function		//
						//
\handler_name :					//
    b .						//
    .size    \handler_name, . - \handler_name	//
.endm						//
// -----------------------------------------------
// -----------------------------------------------
// -----------------------------------------------

//------------------------------------------------------------------------
start:
	mov r1, 0x01
	lsls r2, r1, #29 //r2 0x2000 0000=start
	movs r3, #0x05 //r3 0x05
	lsl r1,r3, #12 //r1 0x0000 5000
	orrs r1,r1,r2 // r1=0x2000 5000 =end
	movs r6,#0
CLEAR_RAM:
	str r6,[r2],#4
	cmp r2,r1
	bcc CLEAR_RAM // branch if r2<r1 очищать, пока меньше конца RAM
//------------------------------------------------------------------------
/* Copying .data section from flash to ram */
// определяем границы

        ldr     r2, =(ld_sdata) 	// адрес начала секции data в RAM
        ldr     r1, =(ld_erodata) 	// по линкеру после констант(rodata) в ROM идут инициализированные переменные(data)
        ldr     r3, =(ld_edata)		// адрес конца секции data в RAM

        b.n     __ir_data_comp


// повторяем цикл пока все данные не будут перекинуты в оперативку
__ir_data_loop:

        ldr.w   r0, [r1], #4
        str.w   r0, [r2], #4

__ir_data_comp:

        cmp     r2, r3
        bne.n   __ir_data_loop
//------------------------------------------------------------------------

	//теперь можно и передавать выполнение программы
	bl main


    DEFAULT_HANDLER main
//------------------------------------------------------------------------


	DEFAULT_HANDLER TIM2_IRQHandler
//: 	.include "sources/IRQ/TIM2Handler.asm"

  	DEFAULT_HANDLER USART1_IRQHandler
//: 	.include "sources/IRQ/USART1Handler.asm"

  	DEFAULT_HANDLER hard_fault
//: 		.include "sources/IRQ/HardFaultHandler.asm"

  	DEFAULT_HANDLER ADC1_2_IRQHandler	//: 	.include "sources/IRQ/ADCHandler.asm"


  // *******faults**********

	DEFAULT_HANDLER nmi_fault
	DEFAULT_HANDLER memory_fault
	DEFAULT_HANDLER bus_fault
	DEFAULT_HANDLER usage_fault

	DEFAULT_HANDLER SVC_Handler
	DEFAULT_HANDLER DebugMon_Handler
	DEFAULT_HANDLER PendSV_Handler
	DEFAULT_HANDLER SysTick_Handler


	DEFAULT_HANDLER WWDG_IRQHandler
	DEFAULT_HANDLER PVD_IRQHandler
	DEFAULT_HANDLER TAMPER_IRQHandler
	DEFAULT_HANDLER RTC_IRQHandler
	DEFAULT_HANDLER FLASH_IRQHandler
	DEFAULT_HANDLER RCC_IRQHandler
	DEFAULT_HANDLER EXTI0_IRQHandler
	DEFAULT_HANDLER EXTI1_IRQHandler
	DEFAULT_HANDLER EXTI2_IRQHandler
	DEFAULT_HANDLER EXTI3_IRQHandler
	DEFAULT_HANDLER EXTI4_IRQHandler
	DEFAULT_HANDLER DMA1_Channel1_IRQHandler
	DEFAULT_HANDLER DMA1_Channel2_IRQHandler
	DEFAULT_HANDLER DMA1_Channel3_IRQHandler
	DEFAULT_HANDLER DMA1_Channel4_IRQHandler
	DEFAULT_HANDLER DMA1_Channel5_IRQHandler
	DEFAULT_HANDLER DMA1_Channel6_IRQHandler
	DEFAULT_HANDLER DMA1_Channel7_IRQHandler
	DEFAULT_HANDLER USB_HP_CAN1_TX_IRQHandler
	DEFAULT_HANDLER USB_LP_CAN1_RX0_IRQHandler
	DEFAULT_HANDLER CAN1_RX1_IRQHandler
	DEFAULT_HANDLER CAN1_SCE_IRQHandler
	DEFAULT_HANDLER EXTI9_5_IRQHandler
	DEFAULT_HANDLER TIM1_BRK_IRQHandler
	DEFAULT_HANDLER TIM1_UP_IRQHandler
	DEFAULT_HANDLER TIM1_TRG_COM_IRQHandler
	DEFAULT_HANDLER TIM1_CC_IRQHandler


	DEFAULT_HANDLER TIM3_IRQHandler
	DEFAULT_HANDLER TIM4_IRQHandler
	DEFAULT_HANDLER I2C1_EV_IRQHandler
	DEFAULT_HANDLER I2C1_ER_IRQHandler
	DEFAULT_HANDLER I2C2_EV_IRQHandler
	DEFAULT_HANDLER I2C2_ER_IRQHandler
	DEFAULT_HANDLER SPI1_IRQHandler
	DEFAULT_HANDLER SPI2_IRQHandler

	DEFAULT_HANDLER USART2_IRQHandler
	DEFAULT_HANDLER USART3_IRQHandler
	DEFAULT_HANDLER EXTI15_10_IRQHandler
	DEFAULT_HANDLER RTCAlarm_IRQHandler
	DEFAULT_HANDLER USBWakeUp_IRQHandler
