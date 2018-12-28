/**
  * @file       main.c
  * @brief      cquque demo
  * @author     redoc <619675912@qq.com>
  * @version    v1.0
  * @date       2018-12-28
  *
  * @note
  * [2018-12-28] <redoc> v1.0
  * 初始版本
  *
  * @remark
  */
  
/* Includes ------------------------------------------------------------------*/
#include "cqueue.h"

/* types ------------------------------------------------------------*/
/* define -----------------------------------------------------------*/
#define QUEUE_EVENT_BUF_SIZE    256
#define QUEUE_UART_BUF_SIZE     512

/* variables --------------------------------------------------------*/
queue_t queue_event;                               	
queue_t queue_uart1_tx;								
uint8_t queue_event_buf[QUEUE_EVENT_BUF_SIZE];     
uint8_t queue_uart1_tx_buf[QUEUE_UART_BUF_SIZE];	

/* macro ------------------------------------------------------------*/
/* functions --------------------------------------------------------*/

void demo_init(void)
{
    queue_init_static(&queue_event,queue_demo_event_buf,QUEUE_EVENT_BUF_SIZE);
    queue_init_static(&queue_uart1_tx,queue_uart1_tx_buf,QUEUE_UART_BUF_SIZE);	
}

void demo_event_change(uint8_t event)
{
    queue_put(&queue_event,event);
}

uint8_t demo_event_check(void)
{
    uint8_t event;
    
    if(false == queue_get(&queue_event,(uint8_t *)&event))
    {
        event = EVENT_NULL;
    }

    return event;
}

uint8_t uart1_send(const uint8_t* buf,uint16_t len)
{
    if( !buf || len <1 )
        return false;
 
    queue_put_length(&queue_uart1_tx,(uint8_t *)buf,len);
    
    return true;
}

void uart_send_process(void)
{
	uint8_t msg_buf[128];
	uint8_t len;
	
    if(queue_get_count(&queue_uart1_tx))
    {
		if(len > 128)
        {
            len = 128;
        }
		
        queue_peek_length(&queue_uart1_tx,msg_buf,len);
		
		//send it
        
        queue_pop_length(&queue_uart1_tx,len);
    }

}

void main(void)
{
	demo_init();
	
	demo_event_change(1);
	uart1_send("hello world!\r\n",sizeof("hello world!\r\n"));
	printf("the event is:%d\r\n",demo_event_check());
	
	while(1)
	{
        uart_send_process();
	}

}
