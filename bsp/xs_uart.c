
#include <stdio.h>

#include "CM3DS_rcc.h"
#include "CM3DS_gpio.h"
#include "CM3DS_uart.h"	
#include "CM3DS_MPS2.h"	

#include "log.h"
#include "xs_uart.h"

/*
STATUS Register (UARTx_STATUS)
[3] RX buffer overrun, write 1 to clear. 
[2] TX buffer overrun, write 1 to clear. 
[1] RX buffer full, read-only. 
[0] TX buffer full, read-only
//1011

CTRL Register (UARTx_CTRL)
[6] High-speed test mode for TXonly. 
[5] RX overrun interrupt enable. 
[4] TX overrun interrupt enable. 
[3] RX interrupt enable. 
[2] TX interrupt enable. 
[1] RX enable. 
[0] TX enable.

INTSTATUS Register (UARTx_INTSTATUS)
[3] RX overrun interrupt. Write 1 toclear. 
[2] TX overrun interrupt. Write 1 toclear. 
[1] RX interrupt. Write 1 to clear. 
[0] TX interrupt. Write 1 to clear.
*/

static TaskHandle_t uart0_task_handle = NULL;
static TaskHandle_t uart1_task_handle = NULL;

static StreamBufferHandle_t uart0_rx_fifo = NULL;
static StreamBufferHandle_t uart0_tx_fifo = NULL;
static StreamBufferHandle_t uart1_rx_fifo = NULL;
static StreamBufferHandle_t uart1_tx_fifo = NULL;
static SemaphoreHandle_t    uart0_tx_sem = NULL;
static SemaphoreHandle_t    uart1_tx_sem = NULL;

unsigned char UartPutc(unsigned char my_ch)
{
  while ((CM3DS_MPS2_UART0->STATE & UART_STATE_TX_FULL)); // Wait if Transmit Holding register is full
  CM3DS_MPS2_UART0->DATA = my_ch; // write to transmit holding register
  return (my_ch);
}

// Get a character
unsigned char UartGetc(void)
{
  while ((CM3DS_MPS2_UART0->STATE & UART_STATE_RX_FULL) == 0 ); // Wait if Receive Holding register is empty
  	return (CM3DS_MPS2_UART0->DATA);
}

struct __FILE { int handle; /* Add whatever you need here */ };
// Verification tests only retarget stdio functions.
#ifndef FPGA_IMAGE
    FILE __stdout;
    FILE __stdin;
#endif

int fputc(int ch, FILE *f) {
  return (UartPutc(ch));
}

int fgetc(FILE *f) {
  return (UartPutc(UartGetc()));
}

void UART0_Handler(void)
{
    if(CM3DS_MPS2_UART0->INTSTATUS & UART_INTSTATUS_RX){
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		do{
			uint8_t recv_data = CM3DS_MPS2_UART0->DATA;
			xStreamBufferSendFromISR(uart0_rx_fifo, &recv_data, 1, &xHigherPriorityTaskWoken);
		}while(CM3DS_MPS2_UART0->STATE & UART_STATE_RX_FULL);
        
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        CM3DS_MPS2_UART0->INTCLEAR = UART_INTCLEAR_RX;
    }
    
    if(CM3DS_MPS2_UART0->INTSTATUS & UART_INTSTATUS_TX){
    	BaseType_t  xHigherPriorityTaskWoken = pdFALSE;
        xSemaphoreGiveFromISR(uart0_tx_sem, &xHigherPriorityTaskWoken);
        
    	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        CM3DS_MPS2_UART0->INTCLEAR = UART_INTCLEAR_TX;
    }
}

void UART1_Handler(void)
{
    if(CM3DS_MPS2_UART1->INTSTATUS & UART_INTSTATUS_RX){
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		do{
			uint8_t recv_data = CM3DS_MPS2_UART1->DATA;
			xStreamBufferSendFromISR(uart1_rx_fifo, &recv_data, 1, &xHigherPriorityTaskWoken);
		}while(CM3DS_MPS2_UART1->STATE & UART_STATE_RX_FULL);
        
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        CM3DS_MPS2_UART1->INTCLEAR = UART_INTCLEAR_RX;
    }
    
    if(CM3DS_MPS2_UART1->INTSTATUS & UART_INTSTATUS_TX){
    	BaseType_t  xHigherPriorityTaskWoken = pdFALSE;
        xSemaphoreGiveFromISR(uart1_tx_sem, &xHigherPriorityTaskWoken);
        
    	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        CM3DS_MPS2_UART1->INTCLEAR = UART_INTCLEAR_TX;
    }
}

size_t xs_uart_fifo_send(int uart_num, uint8_t *buf, uint32_t len, uint32_t timeout)
{
	size_t xSendBytes = 0;
	if(uart_num == UART_NUM0){
		xSendBytes = xStreamBufferSend(uart0_tx_fifo, buf, len, timeout);
	}else if(uart_num == UART_NUM1){
		xSendBytes = xStreamBufferSend(uart1_tx_fifo, buf, len, timeout);
	}
	return xSendBytes;
}

size_t xs_uart_fifo_recv(int uart_num, uint8_t *buf, uint32_t len, uint32_t timeout)
{
	size_t xReceivedBytes = 0;
	if(uart_num == UART_NUM0){
		xReceivedBytes = xStreamBufferReceive(uart0_rx_fifo, buf, len, timeout);
	}else if(uart_num == UART_NUM1){
		xReceivedBytes = xStreamBufferReceive(uart1_rx_fifo, buf, len, timeout);
	}
	return xReceivedBytes;
}

void uart_isr_config(int uart_num, uint8_t ctrl, uint8_t status)
{
	if(uart_num == UART_NUM0){
		NVIC_ClearPendingIRQ(UART0_IRQn);
		if (status){
			CM3DS_MPS2_UART0->CTRL |= ctrl;
			NVIC_EnableIRQ(UART0_IRQn);
		}else {
			CM3DS_MPS2_UART0->CTRL &= ~ctrl;
			NVIC_DisableIRQ(UART0_IRQn);
		}	
	}
	else if(uart_num == UART_NUM1){
		NVIC_ClearPendingIRQ(UART1_IRQn);
		if (status){
			CM3DS_MPS2_UART1->CTRL |= ctrl;
			NVIC_EnableIRQ(UART1_IRQn);
		}else {
			CM3DS_MPS2_UART1->CTRL &= ~ctrl;
			NVIC_DisableIRQ(UART1_IRQn);
		}
	}
}

static void task_uart0_tx(void *pvParameters)
{
    uint8_t send_buf = 0;
    while(1) {
		size_t recv_len = xStreamBufferReceive(uart0_tx_fifo, &send_buf, UART0_FIFO_TX_TRIG, portMAX_DELAY);
		if(recv_len != 0){
			if (xSemaphoreTake(uart0_tx_sem, portMAX_DELAY) == pdTRUE) {
				CM3DS_MPS2_UART0->DATA = send_buf;
			}
		}
    }
}

static void task_uart1_tx(void *pvParameters)
{
    uint8_t send_buf = 0;
    while(1) {
		size_t recv_len = xStreamBufferReceive(uart1_tx_fifo, &send_buf, UART1_FIFO_TX_TRIG, portMAX_DELAY);
		if(recv_len != 0){
			if (xSemaphoreTake(uart1_tx_sem, portMAX_DELAY) == pdTRUE) {
				CM3DS_MPS2_UART1->DATA = send_buf;
			}
		}
    }
}

void xs_uart_fifo_init(int uart_num, uint8_t ctrl, uint32_t bund_rate)
{
	if(uart_num == UART_NUM0){
		//对串口的IO口进行复用，对应复用GPIO2和GPIO3
		UART_InitTypeDef  UART_InitStructure;
		UART_DeInit(CM3DS_MPS2_UART0);
		GPIO_Mode_Set(CM3DS_MPS2_GPIO0, GPIO_Pin_2,GPIO_Mode_AF);
		GPIO_AF_Config( CM3DS_MPS2_GPIO0, GPIO_AF_USART0_RXD, ENABLE); 					//GPIO[2]
		GPIO_Mode_Set(CM3DS_MPS2_GPIO0,GPIO_Pin_3,GPIO_Mode_AF);
		GPIO_AF_Config( CM3DS_MPS2_GPIO0, GPIO_AF_USART0_TXD, ENABLE); 					//GPIO[3]

		UART_InitStructure.UART_BundRate = bund_rate;
		UART_InitStructure.UART_CTRL =  ctrl;	
		UART_Init(CM3DS_MPS2_UART0, &UART_InitStructure);

		if(UART_CTRL_RX_EN & ctrl){
			#if configSUPPORT_STATIC_ALLOCATION == 1
			uart0_rx_fifo = xStreamBufferCreateStatic(UART0_FIFO_RX_DEPATH, UART0_FIFO_RX_TRIG, uart0_rx_fifo_storage, &uart0_rx_fifo_struct);
			#else
			uart0_rx_fifo = xStreamBufferCreate(UART0_FIFO_RX_DEPATH, UART0_FIFO_RX_TRIG);
			#endif
			if(uart0_rx_fifo == NULL){
				XS_LOGE("uart0", "create rx stream buffer error\n");
			}
		}
		if(UART_CTRL_TX_EN & ctrl){
			#if configSUPPORT_STATIC_ALLOCATION == 1
			uart0_tx_fifo = xStreamBufferCreateStatic(UART0_FIFO_TX_DEPATH, UART0_FIFO_TX_TRIG, uart0_tx_fifo_storage, &uart0_tx_fifo_struct);
			#else
			uart0_tx_fifo = xStreamBufferCreate(UART0_FIFO_TX_DEPATH, UART0_FIFO_TX_TRIG);
			#endif
			if(uart0_tx_fifo == NULL){
				XS_LOGE("uart0", "create tx stream buffer error\n");
			}
			#if configSUPPORT_STATIC_ALLOCATION == 1
			uart0_tx_sem = xSemaphoreCreateBinaryStatic(&uart0_tx_sem_buffer);
			#else
			uart0_tx_sem = xSemaphoreCreateBinary();
			#endif
			if(uart0_tx_sem == NULL){
				XS_LOGE("uart0", "create tx Semaphore error\n");
			}
			if(xSemaphoreGive(uart0_tx_sem) != pdTRUE ){
				XS_LOGE("uart0", "Give tx Semaphore error\n");
			}
			#if configSUPPORT_STATIC_ALLOCATION == 1
			uart0_task_handle = xTaskCreateStatic(task_uart0_tx, "task_uart0_tx", UART0_FIFO_TASK, NULL, UART0_FIFO_PRORITY, uart0_task_storage, &uart0_task_buffer );
			#else
			xTaskCreate(task_uart0_tx, "task_uart0_tx", UART0_FIFO_TASK, NULL, UART0_FIFO_PRORITY, &uart0_task_handle);
			#endif
		}
	}else if(uart_num == UART_NUM1){
		
		UART_InitTypeDef  UART_InitStructure;
		UART_DeInit(CM3DS_MPS2_UART1);
		GPIO_Mode_Set(CM3DS_MPS2_GPIO0, GPIO_Pin_4,GPIO_Mode_AF);
		GPIO_AF_Config( CM3DS_MPS2_GPIO0, GPIO_AF_USART0_RXD, ENABLE); 					//GPIO[2]
		GPIO_Mode_Set(CM3DS_MPS2_GPIO0,GPIO_Pin_5,GPIO_Mode_AF);
		GPIO_AF_Config( CM3DS_MPS2_GPIO0, GPIO_AF_USART0_TXD, ENABLE); 					//GPIO[3]

		UART_InitStructure.UART_BundRate = bund_rate;
		UART_InitStructure.UART_CTRL =  ctrl;	
		UART_Init(CM3DS_MPS2_UART1, &UART_InitStructure);

		if(UART_CTRL_RX_EN & ctrl){
			#if configSUPPORT_STATIC_ALLOCATION == 1
			uart1_rx_fifo = xStreamBufferCreateStatic(UART1_FIFO_RX_DEPATH, UART1_FIFO_RX_TRIG, uart1_rx_fifo_storage, &uart1_rx_fifo_struct);
			#else
			uart1_rx_fifo = xStreamBufferCreate(UART1_FIFO_RX_DEPATH, UART1_FIFO_RX_TRIG);
			#endif
			if(uart1_rx_fifo == NULL){
				XS_LOGE("uart1","create rx stream buffer error\n");
			}
		}
		if(UART_CTRL_TX_EN & ctrl){
			#if configSUPPORT_STATIC_ALLOCATION == 1
			uart1_tx_fifo = xStreamBufferCreateStatic(UART1_FIFO_TX_DEPATH, UART1_FIFO_TX_TRIG, uart1_tx_fifo_storage, &uart1_tx_fifo_struct);
			#else
			uart1_tx_fifo = xStreamBufferCreate(UART1_FIFO_TX_DEPATH, UART1_FIFO_TX_TRIG);
			#endif
			if(uart1_tx_fifo == NULL){
				XS_LOGE("uart1", "create tx stream buffer error\n");
			}
			#if configSUPPORT_STATIC_ALLOCATION == 1
			uart1_tx_sem = xSemaphoreCreateBinaryStatic(&uart1_tx_sem_buffer);
			#else
			uart1_tx_sem = xSemaphoreCreateBinary();
			#endif
			if(uart1_tx_sem == NULL){
				XS_LOGE("uart1", "create tx Semaphore error\n");
			}
			if(xSemaphoreGive(uart1_tx_sem) != pdTRUE ){
				XS_LOGE("uart1", "Give tx Semaphore error\n");
			}
			#if configSUPPORT_STATIC_ALLOCATION == 1
			uart1_task_handle = xTaskCreateStatic(task_uart1_tx, "task_uart1_tx", UART1_FIFO_TASK, NULL, UART1_FIFO_PRORITY, uart1_task_storage, &uart1_task_buffer );
			#else
			xTaskCreate(task_uart1_tx, "task_uart1_tx", UART1_FIFO_TASK, NULL, UART1_FIFO_PRORITY, &uart1_task_handle);
			#endif
		}
	}
	if((UART_CTRL_RX_EN & ctrl) && (UART_CTRL_TX_EN & ctrl)){
		uart_isr_config(uart_num, UART_CTRL_RX_INT_EN| UART_CTRL_TX_INT_EN, ENABLE);
	}else if(UART_CTRL_RX_EN & ctrl){
		uart_isr_config(uart_num, UART_CTRL_RX_INT_EN, ENABLE);
	}else if(UART_CTRL_TX_EN & ctrl){
		uart_isr_config(uart_num, UART_CTRL_TX_INT_EN, ENABLE);
	}
}

void xs_uart_fifo_deinit(int uart_num)
{
	uart_isr_config(uart_num, UART_CTRL_RX_INT_EN| UART_CTRL_TX_INT_EN, DISABLE);

	if(uart_num == UART_NUM0){
		if(uart0_rx_fifo != NULL){
			vStreamBufferDelete(uart0_rx_fifo);
		}
		if(uart0_tx_fifo != NULL){
			vStreamBufferDelete(uart0_tx_fifo);
		}
		if(uart0_tx_sem != NULL){
			vSemaphoreDelete(uart0_tx_sem);
		}
		vTaskDelete(uart0_task_handle);
	}else if(uart_num == UART_NUM1){
		if(uart1_rx_fifo != NULL){
			vStreamBufferDelete(uart1_rx_fifo);
		}
		if(uart1_tx_fifo != NULL){
			vStreamBufferDelete(uart1_tx_fifo);
		}
		if(uart1_tx_sem != NULL){
			vSemaphoreDelete(uart1_tx_sem);
		}
		vTaskDelete(uart1_task_handle);
	}
}
