#include"pi.h"
#include"workload.h"

void workload(long long repeat, int thread_id) //并发进程
{
    float x, y, randM = RAND_MAX;
    long long *i = &repeat_threads[thread_id], *sum = &sum_threads[thread_id]; //使用全局变量，以便daemon进程统计运行情况；不同thread使用不同地址以免冲突
    *sum = 0;
    srand(time(0) + thread_id * 10); //不加id可能导致不同thread使用同一种子
    for (*i = 0; *i < repeat; ++*i)
    {
        x = rand() / randM;
        y = rand() / randM;
        *sum += x * x + y * y < 1;
    }
    return;
}

long long input()
{
    long long repeat;
    char temp[10000];
    while(1) //输入及异常处理
    {
        printf("Please input how many times you want to repeat(maximum 1e18 - 1, 1e7~1e10 recommended):");
        scanf("%s", temp);
        if (strlen(temp) > 18)
        {
            printf("Too Large! Please input again.\n");
            system("pause");
            system("cls");
        }
        else
        {
            sscanf(temp, "%lld", &repeat);
            return repeat;
        }
    }
}

void daemon(long long repeat)
{
    int i;
    long long sum, sum_repeat;
    float percentage, elapsed_time = 0;

    for (int i = 0; i < MAX_THREADS; i++) //多线程处理
    {
        std::thread t(workload, repeat / MAX_THREADS + (repeat % MAX_THREADS > i), i); //创建线程
        t.detach(); //同时运行
    }

    while(1)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); //每0.5秒检测一次
        elapsed_time += 0.5;
        sum = 0, sum_repeat = 0;
        for (i = 0; i < MAX_THREADS; i++)
            sum += sum_threads[i], sum_repeat += repeat_threads[i]; //统计运行状况
        system("cls");
        percentage = (float)sum_repeat / repeat * 100;  //输出统计结果
        printf("[");
        int tmp = percentage / 100 * 50;
        for (i = 0; i < tmp; i++)
            printf(">");
        for (; i < 50; i++)
            printf("=");
        printf("] ");
        printf("%.2f%\n", percentage);
        printf("ETC: %lld second(s), Progress: %lld / %lld, Current estimation for Pi: %11.10lf\n",\
         (long long)((repeat - sum_repeat) / (sum_repeat / elapsed_time)), sum_repeat, repeat, (double)sum / sum_repeat * 4);
        if (sum_repeat == repeat)
            break;
    }
    sum = 0, sum_repeat = 0;
    for (i = 0; i < MAX_THREADS; i++)
        sum += sum_threads[i], sum_repeat += repeat_threads[i];
    printf("\nTime used: %.1f second(s), Final estimation for Pi: %11.10lf\n", elapsed_time, (double)sum / sum_repeat * 4);
    system("pause");
}