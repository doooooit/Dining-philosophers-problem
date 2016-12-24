/*********************************************************
 * Author: shangxke <shangke01@gmail.com>
 * Created Date: 2016/12/22
 * Title: 正确的哲学家进餐问题 - 第二种方法
 * Algorithm Description: 任何一个哲学家在申请资源前，
                          先对哲学家的位置进行判断，
                          如果是偶数位，则先申请左边的叉子，后右边的
                          如果是奇数位，则相反
 *********************************************************/

#ifndef PHILOSOPHER_C2
#define PHILOSOPHER_C2

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <string>

#define SLEEP_MAX 10000001
#define RESOURCES 5

// 定义全局资源，在 main 函数中初始化
extern sem_t forks[];             // 资源（叉子）数组，信号量描述
extern int heldBy[];              // 描述叉子被谁持有

// 定义线程，描述哲学家
extern std::string status[];    // 用于描述哲学家状态，

void *philosopher2(void *ID);

#endif
