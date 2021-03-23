#include"pi.h"
#include"workload.h"

long long sum_threads[MAX_CONCURRENCY], repeat_threads[MAX_CONCURRENCY];
int MAX_THREADS = std::min(MAX_CONCURRENCY, (int)std::thread::hardware_concurrency() - 1);
//由于daemon进程休眠需要进入blocking state，故留出一条线程

int main(void)
{
    daemon(input());
}