#include "../inc/bad.h"
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>


//namespace bad {
    // 描述哲学家资源申请过程的函数，先获取第一个资源，再请求第二个资源
    extern void * philosopher0(void * ID) {
        int thisID = *((int *) ID);
        int leftFork = thisID;
        int rightFork = (thisID + 1) % RESOURCES;

        if (!sem_wait(&forks[leftFork])) {
            printf("%d 号哲学家：已获取 %d 号叉子，正在请求 %d 号叉子...\n",
                thisID, leftFork, rightFork);
        }
        sleep(2);
        sem_wait(&forks[rightFork]);

        sem_post(&forks[leftFork]);
        sem_post(&forks[rightFork]);
    }
