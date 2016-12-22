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
#include <string.h>
#include <string>

#include "lib/universe.h"
#include "lib/bad.hpp"
#include "lib/correct1.hpp"
#include "lib/correct2.hpp"
#include "lib/correct3.hpp"

using namespace std;

int main(int argc, char const *argv[]) {

    int type = 0;       // 用于表示执行那个实现

    if (2 == argc) {

        /*
        const string bad = "--bad";
        const string correct1 = "--correct1";
        const string arg = argv[1];
        */

        if (!strcmp(argv[1], "--bad")) {
            type = 0;
        }

        else if (!strcmp(argv[1], "--correct1")) {
            type = 1;
        }

        else if (!strcmp(argv[1], "--correct2")) {
            type = 2;
        }

        else {
            printf("Error: 无效的参数\n");
            printf("\t'--bad'\t\t执行哲学家进餐问题的错误代码\n");
            printf("\t'--correct1'\t执行哲学家进餐问题的第一种正确实现\n");
            printf("\t不传参默认执行错误程序\n");
            exit(1);
        }
    }
    else if (argc > 2) {
        printf("Error: 过多的参数\n");
        printf("\t'--bad'\t\t执行哲学家进餐问题的错误代码\n");
        printf("\t'--correct1'\t执行哲学家进餐问题的第一种正确实现\n");
        printf("\t不传参默认执行错误程序\n");
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



    /***********************
     *线程创建，描述哲学家进餐*
     ***********************/
    int ret;    // 线程创建返回值
    if (0 == type) {
        for (size_t i = 0; i < NUM_THREADS; i++) {
            indexes[i] = i;
            ret = pthread_create(&threadid[i], NULL, bad::philosopher,
                                 (void*) &(indexes[i]));
            if (ret) {
                printf("Error: 创建线程出错\n");
                exit(1);
            } //if
            sleep(1);
        }
    }
    else if (1 == type) {
        correct1::Description();
        for (size_t i = 0; i < NUM_THREADS; i++) {
            indexes[i] = i;
            ret = pthread_create(&threadid[i], NULL, correct1::philosopher
                              , (void*) &(indexes[i]));
            if (ret) {
                printf("Error: 创建线程出错\n");
                exit(1);
            }
        }
    }
    else if (2 == type) {
        correct2::Description();
        for (size_t i = 0; i < NUM_THREADS; i++) {
            indexes[i] = i;
            ret = pthread_create(&threadid[i], NULL, correct2::philosopher
                              , (void*) &(indexes[i]));
            if (ret) {
                printf("Error: 创建线程出错\n");
                exit(1);
            }
        }
    }
    else if (3 == type) {
        correct3::Description();
        for (size_t i = 0; i < NUM_THREADS; i++) {
            indexes[i] = i;
            ret = pthread_create(&threadid[i], NULL, correct3::philosopher
                              , (void*) &(indexes[i]));
            if (ret) {
                printf("Error: 创建线程出错\n");
                exit(1);
            }
        }
    }


    // 回收线程
    for (size_t i = 0; i < NUM_THREADS; i++) {
        pthread_join(threadid[i], NULL);
        printf("%d 号线程已回收\n", i);
    }

    // 销毁锁
    pthread_mutex_destroy(&mutex);

    return 0;
}
