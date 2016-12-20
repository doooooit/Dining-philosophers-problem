/***********************************************************
 * Author: shangxke <shangke01@gmail.com>
 * Created Date: 2016/12/20
 * Title: 正确的哲学家进餐问题的 main 函数，通过主函数参数选择具体实现
 ***********************************************************/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "lib/universe.h"
#include "lib/bad.hpp"
#include "lib/correct1.hpp"

int main(int argc, char const *argv[]) {
    // 资源初始化
    for (size_t i = 0; i < RESOURCES; i++) {
        if (sem_init(&forks[i], 0, 1)) {
            printf("Error: 资源初始化失败\n");
            abort();
        }
    }

    // 互斥锁初始化
    pthread_mutex_init(&mutex, NULL);


    for (size_t i = 0; i < NUM_THREADS; i++) {
        indexes[i] = i;
        int test = pthread_create(&threadid[i], NULL, bad::philosopher
                                 , (void*) &(indexes[i]));
        if (test) {
            printf("Error: 创建线程出错\n");
            abort();
        }
        sleep(1);
    }  //for

    // 回收线程
    for (size_t i = 0; i < NUM_THREADS; i++) {
        pthread_join(threadid[i], NULL);
    }

    return 0;
}
