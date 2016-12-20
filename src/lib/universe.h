/****************************************************
 * Author: shangxke <shangke01@gmail.com>
 * Created Date: 2016/12/20
 * Title: 项目全局头文件，定义了一些全局常量
 ***************************************************/

#ifndef UNIVERSE
#define UNIVERSE

#include <pthread.h>
#include <semaphore.h>


// 定义全局资源，在 main 函数中初始化
#define RESOURCES 5                 // 资源数量
sem_t forks[RESOURCES];             // 资源（叉子）数组，信号量描述

// 定义线程，描述哲学家
#define NUM_THREADS 5               // 最大线程数
pthread_t threadid[NUM_THREADS];    // 线程数组
int indexes[NUM_THREADS];           // 用来记录线程和资源的序号

// 定义互斥锁
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;              // 在 main 函数中动态初始化

#endif
