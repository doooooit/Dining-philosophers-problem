#include "../lib/correct1.h"
#include "../lib/universe.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

extern void *philosopher1(void *ID) {
    int thisID = *((int *) ID);
    int leftFork = thisID;
    int rightFork = (thisID + 1) % RESOURCES;

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
