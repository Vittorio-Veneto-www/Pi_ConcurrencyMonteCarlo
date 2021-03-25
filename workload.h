#include<thread>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<chrono>
#include<cstring>

long long input();
void daemon(long long repeat);
void monte_carlo(long long repeat, int threadId);