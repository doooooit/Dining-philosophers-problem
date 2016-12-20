/**************************************
 * Author: shangxke
 * Created Date: 2016/12/19
 * Title: 错误的哲学家进餐问题
 **************************************/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 定义全局资源(资源数组)
#define RESOURCES 5
sem_t forks[RESOURCES];

// 定义最大线程数
#define NUM_THREADS 5

// 描述哲学家资源申请过程的函数，先获取第一个资源，再请求第二个资源
void * philosopher(void * ID) {
    int id = *((int *) ID);
    if (!sem_wait(&forks[id])) {
        printf("%d 号哲学家：已获取 %d 号叉子，正在请求 %d 号叉子...\n",
            id, id, (id + 1) % 5);
    }

    sleep(2);
    sem_wait(&forks[(id + 1) % 5]);
    sem_post(&forks[id]);
    sem_post(&forks[(id + 1) % 5]);
}

int main(int argc, char const *argv[]) {
    // 资源初始化
    for (size_t i = 0; i < RESOURCES; i++) {
        if (sem_init(&forks[i], 0, 1)) {
            printf("Error: 资源初始化失败\n");
            abort();
        }
    }

    pthread_t threadid[NUM_THREADS];
    int indexes[NUM_THREADS];   // 用来记录线程和资源的序号

    for (size_t i = 0; i < NUM_THREADS; i++) {
        indexes[i] = i;
        int test = pthread_create(&threadid[i], NULL, philosopher
                                 , (void*) &(indexes[i]));
        if (test) {
            printf("Error: 创建线程出错\n");
            abort();
        }
        sleep(1);
    }  //for

    // 回收线程
    for (size_t i = 0; i < NUM_THREADS; i++) {
        pthread_join(threadid[i], NULL);
    }

    return 0;
}
