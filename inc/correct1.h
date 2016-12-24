/*********************************************************
 * Author: shangxke <shangke01@gmail.com>
 * Created Date: 2016/12/20
 * Title: 正确的哲学家进餐问题 - 服务生解法
 * Algorithm Description: 任何一个哲学家在申请资源前，
                          先对所有资源申请加锁，申请完之后释放锁
 *********************************************************/

#ifndef PHILOSOPHER_C1
#define PHILOSOPHER_C1

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <string>


#define SLEEP_MAX 10000001          // 线程随机休眠最大时间
#define RESOURCES 5                 // 资源数量

// 定义全局资源，在 main 函数中初始化
extern sem_t forks[];             // 资源（叉子）数组，信号量描述
extern int heldBy[];              // 描述叉子被谁持有

// 定义线程，描述哲学家
extern std::string status[];    // 用于描述哲学家状态，

// 定义互斥锁
extern pthread_mutex_t mutex;              // 在 main 函数中动态初始化

void *philosopher1(void *ID);

#endif
