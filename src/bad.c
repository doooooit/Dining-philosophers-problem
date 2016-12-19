/**************************************
 * Author: shangxke
 * Created Date: 2016/12/19
 * Title: 错误的哲学家进餐问题
 **************************************/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 定义全局资源(资源数组)
#define RESOURCES 5
pthread_mutex_t mutex[RESOURCES];

// 定义最大线程数
#define NUM_THREADS 5

// 线程函数，先获取第一个资源，再请求第二个资源
void * fetch(void * threadid) {
    int tid = *((int *) threadid);
    pthread_mutex_lock(&mutex[tid]);
    printf("线程 %d 已获取 %d 号资源，正在请求 %d 号资源...\n",
            tid, tid, (tid + 1) % 5);
    sleep(2);
    pthread_mutex_lock(&mutex[(tid + 1) % 5]);
    pthread_mutex_unlock(&mutex[tid]);
    pthread_mutex_unlock(&mutex[(tid + 1) % 5]);
}

int main(int argc, char const *argv[]) {
    // 资源初始化
    for (size_t i = 0; i < RESOURCES; i++) {
        pthread_mutex_init(&mutex[i], NULL);
    }

    pthread_t threadid[NUM_THREADS];
    int indexes[NUM_THREADS];   // 用来记录线程号

    for (size_t i = 0; i < NUM_THREADS; i++) {
        indexes[i] = i;
        int ret = pthread_create(&threadid[i], NULL, fetch
                                 , (void*) &(indexes[i]));
        if (ret) {
            printf("Error: 创建线程出错\n");
            abort();
        }
    }  //for

    for (size_t i = 0; i < RESOURCES; i++) {
        pthread_mutex_destroy(&mutex[i]);
    }

    return 0;
}
