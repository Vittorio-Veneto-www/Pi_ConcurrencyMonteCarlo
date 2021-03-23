#include"pi.h"
#include"workload.h"

long long sum_threads[MAX_CONCURRENCY], repeat_threads[MAX_CONCURRENCY];
int MAX_THREADS = std::min(MAX_CONCURRENCY, (int)std::thread::hardware_concurrency() - 1);
//由于daemon进程休眠需要进入blocking state，故留出一条线程；否则由于CPU的任务调度机制，daemon进程会和计算进程争夺资源，导致输出异常和效率下降

int main(void)
{
    daemon(input());
}