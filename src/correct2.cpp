#include "../inc/correct2.h"

extern void* philosopher2(void* ID) {
    int lowIndex;
    int highIndex;
    int thisID = *((int* ) ID);

    if (thisID < ((thisID + 1) % RESOURCES)) {
        lowIndex = thisID;
        highIndex = (thisID + 1) % RESOURCES;
    } else {
        lowIndex = (thisID + 1) % RESOURCES;
        highIndex = thisID;
    }

    status[thisID] = "Thinking";
    usleep(random() % SLEEP_MAX); // 随机休眠一段时间
    status[thisID] = "Waiting";

    sem_wait(&forks[lowIndex]);
    heldBy[lowIndex] = thisID;
    sem_wait(&forks[highIndex]);
    heldBy[highIndex] = thisID;

    status[thisID] = "Eating";
    usleep(random() % SLEEP_MAX); // 随机休眠一段时间
    status[thisID] = "Terminated";

    sem_post(&forks[highIndex]);
    heldBy[highIndex] = -1;
    sem_post(&forks[lowIndex]);
    heldBy[lowIndex] = -1;

    pthread_exit(NULL);
}