/***********************************************************
 * Author: shangxke <shangke01@gmail.com>
 * Created Date: 2016/12/20
 * Title: correct1.cpp 实现的单元测试
 ***********************************************************/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "universe.h"
#include "correct1.hpp"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char const *argv[]) {
    // 资源初始化
    for (size_t i = 0; i < RESOURCES; i++) {
        if (sem_init(&forks[i], 0, 1)) {
            printf("Error: 资源初始化失败\n");
            exit(1);
        }
    }

    // 互斥锁初始化
    // pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    int test;
    for (size_t i = 0; i < NUM_THREADS; i++) {
        // indexes[i] = i;
        test = pthread_create(&threadid[i], NULL, correct1::philosopher
                                 , (void*) i);

        if (test) {
            printf("Error: 创建线程出错\n");
            exit(1);
        }

    }  //for

    /*
    // 回收线程
    for (size_t i = 0; i < NUM_THREADS; i++) {
        test = pthread_join(threadid[i], NULL);
        if (test) {
            printf("Error: 线程回收错误\n");
        }
        else {
            printf("%d 号线程已回收\n", i);
        }
        sleep(1);
    }
    */
    pthread_join(threadid[0], NULL);
    pthread_join(threadid[1], NULL);
    pthread_join(threadid[2], NULL);
    pthread_join(threadid[3], NULL);
    pthread_join(threadid[4], NULL);

    // 销毁锁
    // pthread_mutex_destroy(&mutex);

    return 0;
}
