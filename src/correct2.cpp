#include "../inc/correct2.h"

extern void *philosopher2(void *ID) {
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
