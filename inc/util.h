/****************************************************
 * Author: shangxke <shangke01@gmail.com>
 * Created Date: 2016/12/20
 * Title: 项目全局头文件，定义了一些全局常量和线程信息打印函数
 ***************************************************/

#ifndef _UNIVERSE_H
#define _UNIVERSE_H

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <string>

#include "../inc/bad.h"
#include "../inc/correct1.h"
#include "../inc/correct2.h"

#define SLEEP_MAX 10000001          // 线程随机休眠最大时间
#define RESOURCES 5                 // 资源数量
#define NUM_THREADS 5               // 最大线程数


// 定义全局资源，在 main 函数中初始化
extern sem_t forks[];             // 资源（叉子）数组，信号量描述
extern int heldBy[];              // 描述叉子被谁持有


// 定义线程，描述哲学家
extern pthread_t threadid[];    // 线程数组
extern int indexes[];           // 用来记录线程和资源的序号
extern std::string status[];    // 用于描述哲学家状态，
                                           // Thinking, Waiting, Eating, Terminated

// 定义互斥锁
extern pthread_mutex_t mutex;              // 在 main 函数中动态初始化


// 显示线程
extern int watcherRun;                 // 执行状态显示开启
extern pthread_t watch;

void *watcher(void*);               // 用于打印各个哲学家的状态和餐叉的使用情况


/***
* 检查控制台输入参数正确性和类型的函数
* 参数表：控制台传给主函数的 int argc, const char * argv[]
* 返回值：参数正确返回一个整型数，表示参数类型
          --bad 返回 0
          --correct1 返回 1
          --correct2 返回 2
          其他值，或参数错误，或参数过多，相应报错
*/
int checkOptions(int, const char **);


/***
* 创建用于描述哲学家行为的线程，有关算法都在这些函数里实现
* createThreads_bad     创建用于演示死锁的错误方法
* createThread_correct1 创建基于服务生算法的哲学家线程
* createThread_correct2 创建基于资源分级算法的哲学家线程
* 无参数，无返回值
*/
void createThreads_bad(void);
void createThread_correct1(void);
void createThread_correct2(void);

#endif
