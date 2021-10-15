#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[])
{
    int n = 0;
    if(argc >= 2) n = atoi(argv[1]);

    // check if n is 1, 2 or 3 
    if(n == 1 || n == 2 || n == 3)
        //system call
        info(n);
    else
        printf("Invalid input. Only 1, 2 and 3 are valid inputs\n");

    exit(0);
}