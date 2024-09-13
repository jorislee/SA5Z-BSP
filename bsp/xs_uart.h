#ifndef __XS_UART_H__
#define __XS_UART_H__

#include "CM3DS_MPS2.h"
			
#include "FreeRTOS.h"
#include "task.h"
#include "stream_buffer.h"
#include "semphr.h"

//////////////////////////////////////////////////////////////////////////////////   	 
/*
STATUS Register (UARTx_STATUS)
[3] RX buffer overrun, write 1 to clear. 
[2] TX buffer overrun, write 1 to clear. 
[1] RX buffer full, read-only. 
[0] TX buffer full, read-only

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

enum uart_port_t {
	UART_NUM0 = 0,
    UART_NUM1 = 1,
    UART_MAX  = 2,
};

#define UART0_FIFO_PRORITY     5
#define UART0_FIFO_TASK        128

#define UART0_FIFO_TX_DEPATH   2048
#define UART0_FIFO_TX_TRIG     1
#define UART0_FIFO_RX_DEPATH   256
#define UART0_FIFO_RX_TRIG     16

#define UART1_FIFO_PRORITY     5
#define UART1_FIFO_TASK        128

#define UART1_FIFO_TX_DEPATH   256
#define UART1_FIFO_TX_TRIG     1
#define UART1_FIFO_RX_DEPATH   256
#define UART1_FIFO_RX_TRIG     16

#define UART_STATE_TX_FULL              ((uint8_t)0x1)
#define UART_STATE_RX_FULL              ((uint8_t)0x2)
#define UART_STATE_TX_OVER           	((uint8_t)0x4)
#define UART_STATE_RX_OVER           	((uint8_t)0x8)

#define UART_INTSTATUS_TX               ((uint8_t)0x01)
#define UART_INTSTATUS_RX               ((uint8_t)0x02)
#define UART_INTSTATUS_TX_OVER          ((uint8_t)0x04)
#define UART_INTSTATUS_RX_OVER          ((uint8_t)0x08)
#define UART_INTCLEAR_TX                ((uint8_t)0x01)
#define UART_INTCLEAR_RX                ((uint8_t)0x02)
#define UART_INTCLEAR_TX_OVER           ((uint8_t)0x04)
#define UART_INTCLEAR_RX_OVER           ((uint8_t)0x08)

#define UART_CTRL_TX_EN                 ((uint8_t)0x01)
#define UART_CTRL_RX_EN                 ((uint8_t)0x02)
#define UART_CTRL_TX_INT_EN             ((uint8_t)0x04)
#define UART_CTRL_RX_INT_EN            	((uint8_t)0x08)
#define UART_CTRL_TX_INT_OVER_EN     	((uint8_t)0x10)
#define UART_CTRL_RX_INT_OVER_EN     	((uint8_t)0x20)

/**
  * @brief Initialize serial port parameters.
  *
  * @param uart_num Uart port number.
  * @param ctrl Uart config parameters(UART_CTRL_TX_EN|UART_CTRL_RX_EN).
  * @param bund_rate Uart config bund_rate(115200).
  *
  */
void xs_uart_fifo_init(int uart_num, uint8_t ctrl, uint32_t bund_rate);

/**
 * @brief Send data to the UART port from a given buffer and length,
 *
 * If the UART driver's parameter 'tx_buffer_size' is set to zero:
 * This function will not return until all the data have been sent out, or at least pushed into TX FIFO.
 *
 * Otherwise, if the 'tx_buffer_size' > 0, this function will return after copying all the data to tx ring buffer,
 * UART ISR will then move data from the ring buffer to TX FIFO gradually.
 *
 * @param uart_num Uart port number.
 * @param buf   data buffer address
 * @param len  data length to send
 * @param timeout  waiting time to send
 *
 * @return
 *     - (0) Parameter error
 *     - OTHERS (>=0) The number of bytes pushed to the TX FIFO
 */
size_t xs_uart_fifo_send(int uart_num, uint8_t *buf, uint32_t len, uint32_t timeout);

/**
 * @brief UART read bytes from UART buffer
 *
 * @param uart_num Uart port number.
 * @param buf     pointer to the buffer.
 * @param len  data length
 * @param timeout sTimeout, count in RTOS ticks
 *
 * @return
 *     - (0) Error
 *     - OTHERS (>=0) The number of bytes read from UART FIFO
 */
size_t xs_uart_fifo_recv(int uart_num, uint8_t *buf, uint32_t len, uint32_t timeout);

/**
  * @brief Uninstall initialized serial port.
  *
  * @param uart_num Uart port number.
  *
  */
void xs_uart_fifo_deinit(int uart_num);

#endif /* __XS_UART_H__ */
