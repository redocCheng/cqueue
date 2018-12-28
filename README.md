# cqueue

## 介绍
一个环形队列缓冲区，支持单个、多个和全部操作方式。

## 函数列表
```
uint8_t queue_put(queue_t *queue,uint8_t ch);
uint8_t queue_put_length(queue_t *queue,uint8_t *buffer,uint16_t length);
uint8_t queue_get(queue_t *queue,uint8_t *ch);
uint8_t queue_peek(queue_t *queue,uint8_t *ch);
uint8_t queue_peek_length(queue_t *queue,uint8_t *buffer,uint16_t length);
uint8_t queue_peek_all(queue_t *queue,uint8_t *buffer);
void queue_pop(queue_t *queue);
void queue_pop_length(queue_t *queue,uint16_t length);
void queue_pop_all(queue_t *queue);

```

## 使用方法
### 1、初始化
```

#define QUEUE_BUF_SIZE     512                      //定义缓冲区长度
uint8_t queue_event_buf[QUEUE_EVENT_BUF_SIZE];      //定义缓冲区
queue_t queue_event;                                //定义队列句柄


queue_init_static(&queue_event,queue_event_buf,QUEUE_BUF_SIZE);  //初始化

```

### 2、使用

[main.c](https://github.com/redocCheng/cqueue/tree/master/demo/main.c) 简单介绍了实际中的一些使用方法


