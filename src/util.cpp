/****************************************************
 * Author: shangxke <shangke01@gmail.com>
 * Created Date: 2016/12/23
 * Title: 项目全局头文件 util.h 的库
 ***************************************************/

/**
 * 打印程序执行过程中各个哲学家的状态和餐叉的使用情况
 */

#include "../inc/util.h"


void *watcher(void*) {
    int thinking; // 正在思考中的哲学家数
    int waiting; // 正在等待的哲学家数
    int eating; // 正在吃东西的哲学家数
    int use; // 正在使用的筷子数
    int available; // 当前可用的筷子数

    int N = RESOURCES;

    while (watcherRun) {
        system("clear");

        //start printing
        printf("哲学家编号   状态          叉子编号  被谁持有\n");
        thinking = 0;
        waiting = 0;
        eating = 0;
        use = 0;
        available = 0;

        for (size_t i = 0; i < N; i++) {
            if (heldBy[i] != -1) {
                printf("[%d]:         %-14s[%d]:      %d\n", i, status[i].c_str(), i, heldBy[i]);
                use++;
            } else {
                printf("[%d]:         %-14s[%d]:      Free\n", i, status[i].c_str(), i);
                available++;
            }

            if (!strcmp(status[i].c_str(), "Thinking"))
                thinking++;
            else if (!strcmp(status[i].c_str(), "Waiting"))
                waiting++;
            else if (!strcmp(status[i].c_str(), "Eating"))
                eating++;
        } // for

        printf("\n【哲学家概览】\n思考中：%2d\t等待中：%2d\t进餐中：%2d\n", thinking, waiting, eating);
        printf("\n【筷子概览】\n使用中：%2d\t可用数：%2d\n\n", use, available);

        usleep(500000);
    }

    pthread_exit(NULL);
}


/**
 * 用于检查用户在控制台输入的参数的正确性和类型
 * 参数：主函数 int argc, char *argv[]
 * 返回：一个整型数，用于表示参数的类型
 */
int checkOptions(int argc, const char * argv[]) {
    if (2 == argc) {
        if (!strcmp(argv[1], "--bad")) {
            return 0;
        } else if (!strcmp(argv[1], "--correct1")) {
            return 1;
        } else if (!strcmp(argv[1], "--correct2")) {
            return 2;
        } else {
            printf("Error: 无效的参数\n");
            printf("\t'--bad'\t\t执行哲学家进餐问题的错误代码，发生死锁\n");
            printf("\t'--correct1'\t执行哲学家进餐问题的服务生算法\n");
            printf("\t'--correct1'\t执行哲学家进餐问题的资源分级算法\n");
            printf("\t不传参默认执行错误程序\n");
            exit(1);
        }
    } else if (argc > 2) {
        printf("Error: 过多的参数\n");
        printf("\t'--bad'\t\t执行哲学家进餐问题的错误代码，发生死锁\n");
        printf("\t'--correct1'\t执行哲学家进餐问题的服务生算法\n");
        printf("\t'--correct1'\t执行哲学家进餐问题的资源分级算法\n");
        printf("\t不传参默认执行错误程序\n");
        exit(1);
    }
}


/***
 * 创建线程（组）函数，无参数，无返回值
 */

// 创建用于演示死锁的线程
void createThreads_bad(void) {
    int ret; // 用于存储 pthread_create 返回值，检查线程创建是否成功
    for (size_t i = 0; i < NUM_THREADS; i++) {
        indexes[i] = i; // util.h 中声明的数组，表示哲学家和餐叉的序号
        ret = pthread_create(&threadid[i], NULL, philosopher0,
            (void * ) & (indexes[i]));
        if (ret) {
            printf("Error: 创建线程出错\n");
            exit(1);
        } //if
        sleep(1);
    }
}

// 创建服务生算法线程
void createThread_correct1(void) {
    int ret; // 用于存储 pthread_create 返回值，检查线程创建是否成功
    for (size_t i = 0; i < NUM_THREADS; i++) {
        indexes[i] = i;
        ret = pthread_create(&threadid[i], NULL, philosopher1, (void*) &(indexes[i]));
        if (ret) {
            printf("Error: 创建线程出错\n");
            exit(1);
        }
    }
}

// 创建资源分级算法线程
void createThread_correct2(void) {
    int ret; // 用于存储 pthread_create 返回值，检查线程创建是否成功
    for (size_t i = 0; i < NUM_THREADS; i++) {
        indexes[i] = i;
        ret = pthread_create( & threadid[i], NULL, philosopher2, (void * ) & (indexes[i]));
        if (ret) {
            printf("Error: 创建线程出错\n");
            exit(1);
        }
    }
}