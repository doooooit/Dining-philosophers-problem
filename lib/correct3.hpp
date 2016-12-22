/*********************************************************
 * Author: shangxke <shangke01@gmail.com>
 * Created Date: 2016/12/22
 * Title: 正确的哲学家进餐问题 - 第三种方法
 * Algorithm Description: 1~4 号哲学家按先左后右顺序申请资源
                          第5号哲学家顺序改为先右后左
 *********************************************************/

#ifndef PHILOSOPHER_C2
#define PHILOSOPHER_C2

#include "universe.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>


namespace correct3 {
    void Description() {
        printf("$\n");
        printf("$ Title: 第三种正确解法\n");
        printf("$ Algorithm Description:\n");
        printf("$\t1~4 号哲学家按先左后右顺序申请资源\n");
        printf("$\t第5号哲学家顺序改为先右后左\n");
        printf("$\n\n");
    }


    void *philosopher(void *ID) {
        int id = *((int *) ID);
        int next = (id + 1) % 5;

        // 位置判断
        if (id < 4) {
            // 偶数位
            // 请求资源
            if (!sem_wait(&forks[id])) {
                printf("%d 哲学家：已获得 %d 号叉子\n", id, id);
            }
            if (!sem_wait(&forks[next])) {
                printf("%d 哲学家：已获得 %d 号叉子\n", id, next);
            }
        }
        else {
            if (!sem_wait(&forks[next])) {
                printf("%d 哲学家：已获得 %d 号叉子\n", id, next);
            }
            if (!sem_wait(&forks[id])) {
                printf("%d 哲学家：已获得 %d 号叉子\n", id, id);
            }
        }

        printf("%d 哲学家：正在进餐\n", id);

        sem_post(&forks[id]);
        sem_post(&forks[next]);
        pthread_exit(NULL);
    }

}

#endif
