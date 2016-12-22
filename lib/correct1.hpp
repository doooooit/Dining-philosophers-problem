/*********************************************************
 * Author: shangxke <shangke01@gmail.com>
 * Created Date: 2016/12/20
 * Title: 正确的哲学家进餐问题 - 服务生解法
 * Algorithm Description: 任何一个哲学家在申请资源前，
                          先对所有资源申请加锁，申请完之后释放锁
 *********************************************************/

#ifndef PHILOSOPHER_C1
#define PHILOSOPHER_C1

#include "universe.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>


namespace correct1 {
    void Description() {
        printf("$\n");
        printf("$ Title: 服务生解法\n");
        printf("$ Algorithm Description:\n");
        printf("$\t任何一个哲学家在申请资源前\n");
        printf("$\t必须先获得服务生的服务，即对资源加锁\n");
        printf("$\t同时获得所需的两个资源后释放服务生（锁）\n");
        printf("$\t缺点：并行性差，如果一个哲学家在进餐时其相邻的哲学家申请，则所有线程都阻塞\n");
        printf("$\n\n");
    }


    void *philosopher(void *ID) {
        int thisID = *((int *) ID);
        int leftFork = thisID;
        int rightFork = (thisID + 1) % 5;

        status[thisID] = "Thinking";
        usleep(random() % SLEEP_MAX);   // 随机休眠一段时间
        status[thisID] = "Waiting";

        pthread_mutex_lock(&mutex);  // 申请资源前先上锁
        // 请求资源
        sem_wait(&forks[leftFork]);
        heldBy[leftFork] = thisID;
        sem_wait(&forks[rightFork]);
        heldBy[rightFork] = thisID;

        status[thisID] = "Eating";
        pthread_mutex_unlock(&mutex);

        usleep(random() % SLEEP_MAX);   // 随机休眠一段时间

        status[thisID] = "Terminated";

        // 释放叉子
        sem_post(&forks[leftFork]);
        heldBy[leftFork] = -1;
        sem_post(&forks[rightFork]);
        heldBy[rightFork] = -1;

        pthread_exit(NULL);
    }

}

#endif
