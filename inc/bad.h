/**************************************
 * Author: shangxke
 * Created Date: 2016/12/19
 * Title: 错误的哲学家进餐问题
 **************************************/

#ifndef BAD
#define BAD

#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define RESOURCES 5                 // 资源数量

// 定义全局资源，在 main 函数中初始化
extern sem_t forks[];             // 资源（叉子）数组，信号量描述

void * philosopher0(void * ID) ;

#endif
