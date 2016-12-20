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

namespace bad {
    // 描述哲学家资源申请过程的函数，先获取第一个资源，再请求第二个资源
    void * philosopher(void * ID) {
        int id = *((int *) ID);
        int next = (id + 1) % 5;
        if (!sem_wait(&forks[id])) {
            printf("%d 号哲学家：已获取 %d 号叉子，正在请求 %d 号叉子...\n",
                id, id, next);
        }
        sleep(2);
        sem_wait(&forks[next]);
        sem_post(&forks[id]);
        sem_post(&forks[next]);
    }

}

#endif
