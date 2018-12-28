/**
  * @file       cqueue.h
  * @brief      队列驱动头文件
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CQUEUE_H
#define __CQUEUE_H
/* Includes ------------------------------------------------------------------*/

#include "stdint.h"
#include "stdio.h"

/**
  * @addtogroup SYSTEM驱动
  * @{
  */

/**
  * @addtogroup 队列驱动
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * @defgroup 队列驱动类型定义
  * @{
  */
  
/**
  * @brief 队列数据类型
  */
typedef struct {
    uint8_t *buffer;        /**<  数据缓冲区       */
    uint16_t max_size;      /**<  数据最大长度   */
    uint16_t front;         /**<  数据头           */
    uint16_t rear;          /**<  数据尾           */
    
}queue_t;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/**
  * @defgroup 队列驱动外部调用函数声明
  * @{
  */
void queue_init_static(queue_t *queue, uint8_t *buffer, uint16_t max_size);
uint16_t queue_get_count(queue_t *queue);
uint8_t queue_is_full(queue_t *queue);
uint8_t queue_is_empty(queue_t *queue);
uint16_t queue_get_size(queue_t *queue);
uint8_t queue_put(queue_t *queue,uint8_t ch);
uint8_t queue_put_length(queue_t *queue,uint8_t *buffer,uint16_t length);
uint8_t queue_get(queue_t *queue,uint8_t *ch);
uint8_t queue_peek(queue_t *queue,uint8_t *ch);
uint8_t queue_peek_length(queue_t *queue,uint8_t *buffer,uint16_t length);
uint8_t queue_peek_all(queue_t *queue,uint8_t *buffer);
void queue_pop(queue_t *queue);
void queue_pop_length(queue_t *queue,uint16_t length);
void queue_pop_all(queue_t *queue);
/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/









#endif

