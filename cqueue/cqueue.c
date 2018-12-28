/**
  * @file       cqueue.c
  * @brief      队列驱动文件
  * @author     redoc
  * @version    v1.0
  * @date       2016-08-20
  *
  * @note
  * [2016-08-20] <redoc> (v1.0) 
  * 初始版本
  *
  * @remark
  */
/* Includes ------------------------------------------------------------------*/
#include "cqueue.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/**
  * @addtogroup SYSTEM驱动
  * @{
  */

/**
  * @addtogroup 队列驱动
  * @{
  */

  


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/**
  * @defgroup 队列驱动外部函数定义
  * @{
  */
/**
  * @brief    初始化队列
  * @param    *QUEUE：队列对象
  * @param    *buffer：队列数组首地址
  * @param    max_size：队列容量
  *
  * @return    void    
  * @remark        
  */
void queue_init_static(queue_t *queue, uint8_t *buffer, uint16_t max_size) 
{
    queue->buffer = buffer;
    queue->max_size = max_size;
    queue->front = queue->rear = 0;
}

/**
  * @brief    计算队列数据个数
  * @param    *QUEUE：队列对象
  *
  * @return    uint8_t:队列数据个数    
  * @remark        
  */
uint16_t  queue_get_count(queue_t *queue)
{
    if(queue->front < queue->rear)
        return queue->front + queue->max_size - queue->rear;
    else
        return queue->front - queue->rear;
}

/**
  * @brief    检测队列满
  * @param    *QUEUE：队列对象
  *
  * @return    uint8_t:队列满状态
  * @remark        
  */
uint8_t queue_is_full(queue_t *queue)
{
    return (queue_get_count(queue)  == (queue->max_size - 1));
};

/**
  * @brief    检测队列空
  * @param    *QUEUE：队列对象
  *
  * @return    uint8_t:队列空状态
  * @remark        
  */
uint8_t queue_is_empty(queue_t *queue)
{
    return queue_get_count(queue) == 0;
};

/**
  * @brief    获取队列容量
  * @param    *QUEUE：队列对象
  *
  * @return    uint16_t:队列容量
  * @remark        
  */
uint16_t queue_get_size(queue_t *queue)
{    
    return queue->max_size;
};

/**
  * @brief    将队列成员放入队列
  * @param    *QUEUE：队列对象
  * @param    ch：数据
  *
  * @return    uint8_t:运行状态
  * @remark        
  */
uint8_t queue_put(queue_t *queue,uint8_t ch)
{
      if(!queue_is_full(queue))
      {
        queue->buffer[queue->front]= ch;
        queue->front ++;
        queue->front %= queue->max_size; 
        return true;
      }
      else
        return false;
}

/**
  * @brief    将指定长度队列成员放入队列
  * @param    *QUEUE：队列对象
  * @param    *buffer：数据首地址
  * @param    length：数据长度
  *
  * @return    uint8_t:运行状态
  * @remark        
  */
uint8_t queue_put_length(queue_t *queue,uint8_t *buffer,uint16_t length)
{
    int i;
    
    if(!((queue_get_size(queue)-queue_get_count(queue))<=length))
    {
        for (i = 0; i < length; ++i)
        {
            queue->buffer[queue->front]= *(buffer++);
            queue->front ++;
            queue->front %= queue->max_size; 
        }
        return true;
    }
    else
        return false;
}
/**
  * @brief    将队列成员取出队列
  * @param    *QUEUE：队列对象
  * @param    ch：数据
  *
  * @return    uint8_t:运行状态
  * @remark        
  */
uint8_t queue_get(queue_t *queue,uint8_t *ch)
{
      if (!queue_is_empty(queue))
      {
        *ch = queue->buffer[queue->rear];
        queue->rear++;
        queue->rear%=queue->max_size;   
        return true;
      }
      else
        return 0;
}

/**
  * @brief    检查数据，但是不弹出数据
  * @param    *QUEUE：队列对象
  * @param    ch：数据
  *
  * @return    uint8_t:运行状态
  * @remark        
  */
uint8_t queue_peek(queue_t *queue,uint8_t *ch)
{
      if (!queue_is_empty(queue))
      {
        *ch = queue->buffer[queue->rear];
        return true;
      }
      else
        return false;
}

/**
  * @brief    检查指定长度数据，但是不弹出数据
  * @param    *QUEUE：队列对象
  * @param    *buffer：数据首地址
  * @param    length：数据长度
  *
  * @return    uint8_t:运行状态
  * @remark        
  */
uint8_t queue_peek_length(queue_t *queue,uint8_t *buffer,uint16_t length)
{
    int i;
    uint8_t     rt = false;
    for (i = 0; i < length; ++i)
    {
        *(buffer++) = queue->buffer[(queue->rear + i) % queue->max_size];
        rt = true;
    }

    return rt;
}

/**
  * @brief    检查所有数据，但是不弹出数据
  * @param    *QUEUE：队列对象
  * @param    *buffer：数据首地址
  *
  * @return    uint8_t:运行状态
  * @remark        
  */
uint8_t queue_peek_all(queue_t *queue,uint8_t *buffer)
{
    int back_tail;
    uint8_t     rt = false;
    if( !buffer ) return false;

    back_tail = queue->rear;
    
    while (back_tail != queue->front)
    {
        *(buffer++) = queue->buffer[back_tail];
        ++back_tail;
        back_tail %= queue->max_size;
        rt = true;
    }

    return rt;
}

/**
  * @brief    POP一个数据，不使用数据
  * @param    *QUEUE：队列对象
  *
  * @return    uint8_t:运行状态
  * @remark        
  */
void queue_pop(queue_t *queue)
{
      if (!queue_is_empty(queue))
      {
        queue->rear++;
        queue->rear%=queue->max_size;   
      }
}

/**
  * @brief    POP指定长的数据，不使用数据
  * @param    *QUEUE：队列对象
  * @param    pos：长度
  *
  * @return    uint8_t:运行状态
  * @remark        
  */
void queue_pop_length(queue_t *queue,uint16_t length)
{
      if (!queue_is_empty(queue))
      {
        queue->rear+=length;
        queue->rear%=queue->max_size;   
      }
}

/**
  * @brief    POP所有数据，不使用数据
  * @param    *QUEUE：队列对象
  *
  * @return    uint8_t:运行状态
  * @remark        
  */
void queue_pop_all(queue_t *queue)
{
    queue->front = 0;
    queue->rear = 0;
}
  
/**
  * @}
  */

/**
  * @}
  */
  
/**
  * @}
  */




