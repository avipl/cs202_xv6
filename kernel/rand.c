// A pseudo random generator based on LCG with glibc's parameter
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "rand.h"

int x = 1;

void srand(int seed){
    x = seed;
    return;
}

int rand(void){
    long long tmp = (1103515245*x + 12345) % 2147483647;
    while(tmp < 0){
        tmp += 2147483647;
    }
    x = (int) tmp;
    return x;
}