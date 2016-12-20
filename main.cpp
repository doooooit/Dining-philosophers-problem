/***********************************************************
 * Author: shangxke <shangke01@gmail.com>
 * Created Date: 2016/12/20
 * Title: 哲学家进餐问题的 main 函数，通过主函数参数选择具体实现
 ***********************************************************/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>

#include "lib/universe.h"
#include "lib/bad.hpp"
#include "lib/correct1.hpp"

using namespace std;

int main(int argc, char const *argv[]) {

    int type = 1;       // 用于表示执行那个实现

    if (2 == argc) {

        const string bad = "--bad";
        const string correct1 = "--correct1";
        const string arg = argv[1];

        if (bad == arg) {
            type = 0;
        }

        else if (correct1 == arg) {
            type = 1;
        }

        else {
            printf("Error: 无效的参数\n");
            printf("\t'--bad'\t\t执行哲学家进餐问题的错误代码\n");
            printf("\t'--correct1'\t执行哲学家进餐问题的第一种正确实现\n");
            printf("\t不传参默认以第一种正确实现执行\n");
            exit(1);
        }
    }
    else if (argc > 2) {
        printf("Error: 过多的参数\n");
        printf("\t'--bad'\t\t执行哲学家进餐问题的错误代码\n");
        printf("\t'--correct1'\t执行哲学家进餐问题的第一种正确实现\n");
        printf("\t不传参默认以第一种正确实现执行\n");
        exit(1);
    }

    // 资源初始化
    for (size_t i = 0; i < RESOURCES; i++) {
        if (sem_init(&forks[i], 0, 1)) {
            printf("Error: 资源初始化失败\n");
            exit(1);
        }
    }

    // 互斥锁初始化
    pthread_mutex_init(&mutex, NULL);


    for (size_t i = 0; i < NUM_THREADS; i++) {
        indexes[i] = i;
        int test;
        if (0 == type) {
            test = pthread_create(&threadid[i], NULL, bad::philosopher
                                 , (void*) &(indexes[i]));
        }
        if (1 == type) {
            test = pthread_create(&threadid[i], NULL, correct1::philosopher
                                 , (void*) &(indexes[i]));
        }

        if (test) {
            printf("Error: 创建线程出错\n");
            exit(1);
        }

        if (type == 0) {
            sleep(1);
        }
    }  //for

    // 回收线程
    for (size_t i = 0; i < NUM_THREADS; i++) {
        pthread_join(threadid[i], NULL);
        printf("%d 号线程已回收\n", i);
    }

    // 销毁锁
    pthread_mutex_destroy(&mutex);

    return 0;
}
