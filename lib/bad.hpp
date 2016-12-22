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
#include <stdlib.h>

namespace bad {
    // 描述哲学家资源申请过程的函数，先获取第一个资源，再请求第二个资源
    void * philosopher(void * ID) {
        int thisID = *((int *) ID);
        int leftFork = thisID;
        int rightFork = (thisID + 1) % 5;

        status[thisID] = "Thinking";

        status[thisID] = "Waiting";

        if (!sem_wait(&forks[leftFork])) {
            printf("%d 号哲学家：已获取 %d 号叉子，正在请求 %d 号叉子...\n",
                thisID, leftFork, rightFork);
        }
        sleep(2);
        sem_wait(&forks[rightFork]);
        sem_post(&forks[leftFork]);
        sem_post(&forks[rightFork]);
    }

}

#endif
