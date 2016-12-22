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


namespace correct2 {
    void Description() {
        printf("$\n");
        printf("$ Title: 第二种正确解法\n");
        printf("$ Algorithm Description:\n");
        printf("$\t任何一个哲学家在申请资源前，先对哲学家的位置进行判断，\n");
        printf("$\t如果是偶数位，则先申请左边的叉子，后右边的\n");
        printf("$\t如果是奇数位，则相反\n");
        printf("$\n\n");
    }


    void *philosopher(void *ID) {
        int id = *((int *) ID);
        int next = (id + 1) % 5;

        // 位置判断
        if (!(id % 2)) {
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
