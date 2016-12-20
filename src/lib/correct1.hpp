/*********************************************************
 * Author: shangxke <shangke01@gmail.com>
 * Created Date: 2016/12/20
 * Title: 正确的哲学家进餐问题
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
    void *philosopher(void *ID) {
        int id = *((int *) ID);
        int next = id + 1;

        pthread_mutex_lock(&mutex);  // 申请资源前先上锁
        // 请求资源
        if (!sem_wait(&forks[id])) {
            printf("%d 哲学家：已获得 %d 号叉子\n", id, id);
        }
        if (!sem_wait(&forks[next])) {
            printf("%d 哲学家：已获得 %d 号叉子\n", id, next);
        }
        pthread_mutex_unlock(&mutex);

        printf("%d 哲学家：正在进餐\n", id);

        sem_post(&forks[id]);
        sem_post(&forks[next]);
    }

}

#endif
