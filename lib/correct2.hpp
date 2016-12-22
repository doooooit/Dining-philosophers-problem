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

#include "universe.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>


namespace correct2 {
    void *philosopher(void *ID) {
        int thisID = *((int *) ID);
        int leftFork = thisID;
        int rightFork = (thisID + 1) % RESOURCES;

        status[thisID] = "Thinking";
        usleep(random() % SLEEP_MAX);   // 随机休眠一段时间
        status[thisID] = "Waiting";

        // 判断资源序号
        if (leftFork < rightFork) {
            // 请求资源
            sem_wait(&forks[leftFork]);
            heldBy[leftFork] = thisID;
            sem_wait(&forks[rightFork]);
            heldBy[rightFork] = thisID;

            status[thisID] = "Eating";
            usleep(random() % SLEEP_MAX);   // 随机休眠一段时间
            status[thisID] = "Terminated";

            sem_post(&forks[rightFork]);
            heldBy[rightFork] = -1;
            sem_post(&forks[leftFork]);
            heldBy[leftFork] = -1;
        }
        else {
            sem_wait(&forks[rightFork]);
            heldBy[rightFork] = thisID;
            sem_wait(&forks[leftFork]);
            heldBy[leftFork] = thisID;

            status[thisID] = "Eating";
            usleep(random() % SLEEP_MAX);   // 随机休眠一段时间
            status[thisID] = "Terminated";

            sem_post(&forks[leftFork]);
            heldBy[leftFork] = -1;
            sem_post(&forks[rightFork]);
            heldBy[rightFork] = -1;
        }


        pthread_exit(NULL);
    }

}

#endif
