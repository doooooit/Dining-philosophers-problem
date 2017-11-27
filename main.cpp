/**
 * Author: shangxke <shangke01@gmail.com>
 * Created Date: 2016/12/20
 * Title: 哲学家进餐问题的 main 函数，通过主函数参数选择具体实现
 */

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "inc/util.h"


// 定义全局资源，在 main 函数中初始化
sem_t forks[RESOURCES];             // 资源（叉子）数组，信号量描述
int heldBy[RESOURCES];              // 描述叉子被谁持有


// 定义线程，描述哲学家
pthread_t threadid[NUM_THREADS];    // 线程数组
int indexes[NUM_THREADS];           // 用来记录线程和资源的序号
std::string status[NUM_THREADS];    // 用于描述哲学家状态，
                                           // Thinking, Waiting, Eating, Terminated

// 定义互斥锁
pthread_mutex_t mutex;              // 在 main 函数中动态初始化


// 显示线程
int watcherRun;                 // 执行状态显示开启
pthread_t watch;


int main(int argc, char const *argv[]) {


    int type = 0;       // 用于表示执行那个实现

    // 检查控制台输入参数的正确性和类型，util.h中声明
    type = checkOptions(argc, argv);

    // 资源初始化
    for (size_t i = 0; i < RESOURCES; i++) {
        heldBy[i] = -1;     // 当前无人持有
        if (sem_init(&forks[i], 0, 1)) {
            printf("Error: 资源初始化失败\n");
            exit(1);
        }
    }


    // 互斥锁初始化
    pthread_mutex_init(&mutex, NULL);



    /***
     * 线程创建，描述哲学家进餐*
     */
    if (0 == type) {
        createThreads_bad();
    }
    else if (1 == type) {
        createThread_correct1();
    }
    else if (2 == type) {
        createThread_correct2();
    }

    if (0 != type) {
        // 创建显示线程
        watcherRun = 1;
        pthread_create(&watch, NULL, watcher, NULL);
    }

    // 回收线程
    for (size_t i = 0; i < NUM_THREADS; i++) {
        pthread_join(threadid[i], NULL);
    }
    sleep(1);

    if (0 != type) {
        watcherRun = 0;
        pthread_join(watch, NULL);
    }

    // 销毁锁
    pthread_mutex_destroy(&mutex);

    return 0;
}
