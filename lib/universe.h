/****************************************************
 * Author: shangxke <shangke01@gmail.com>
 * Created Date: 2016/12/20
 * Title: 项目全局头文件，定义了一些全局常量
 ***************************************************/

#ifndef UNIVERSE
#define UNIVERSE

#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <string>

#define SLEEP_MAX 10000001          // 线程随机休眠最大时间


// 定义全局资源，在 main 函数中初始化
#define RESOURCES 5                 // 资源数量
sem_t forks[RESOURCES];             // 资源（叉子）数组，信号量描述
int heldBy[RESOURCES];              // 描述叉子被谁持有

// 定义线程，描述哲学家
#define NUM_THREADS 5               // 最大线程数
pthread_t threadid[NUM_THREADS];    // 线程数组
int indexes[NUM_THREADS];           // 用来记录线程和资源的序号
std::string status[NUM_THREADS];         // 用于描述哲学家状态，
                                    // Thinking, Waiting, Eating, Terminated
// 定义互斥锁
pthread_mutex_t mutex;              // 在 main 函数中动态初始化

int watcherRun = 1;                  // 执行状态显示开启

// 显示线程
pthread_t watch;
void *watcher(void*) {
    int thinking;           // 正在思考中的哲学家数
	int waiting;            // 正在等待的哲学家数
    int eating;             // 正在吃东西的哲学家数
    int use;              // 正在使用的筷子数
    int available;          // 当前可用的筷子数

    int N = RESOURCES;

	while (watcherRun) {
		//wait for 0.5 seconds
		usleep(500000);

		//start printing
		printf("哲学家编号   状态               叉子编号    被谁持有\n");
		thinking = 0; waiting = 0; eating = 0;	use = 0; available = 0;

		for (size_t i = 0; i < N; i++) {
			if (heldBy[i] != -1) {
				printf("[%2d]:   %-20s[%2d]:   %d\n",i,status[i],i,heldBy[i]);
				use++;
			} else {
				printf("[%2d]:   %-20s[%2d]:   Free\n",i,status[i],i);
				available++;
			}

			if (!strcmp(status[i].c_str(),"Thinking"))
				thinking++;
			else if (!strcmp(status[i].c_str(),"Waiting"))
				waiting++;
			else if (!strcmp(status[i].c_str(),"Eating"))
				eating++;

		}
		printf("\n【哲学家概览】\n思考中：%2d\t等待中：%2d\t进餐中：%2d\n", thinking, waiting, eating);
        printf("\n【筷子概览】\n使用中：%2d  可用数：%2d\n\n\n", use, available);
	}

	pthread_exit(NULL);
}

#endif
