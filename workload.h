#include<thread>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<chrono>
#include<cstring>

void workload(long long repeat, int threadId);
long long input();
void daemon(long long repeat);