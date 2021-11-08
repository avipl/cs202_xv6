#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){

    int ticket = 30;
    assign(ticket);
    // char name[16] = "prog1";
    // assign(ticket, name);
    
    //occupy the CPU 
    int i,k;
    const int loop = 50000;
    for (i = 0; i < loop; i++)
    {
        asm("nop");
        for(k=0; k<loop; k++){
            asm("nop");
        }
    }

    printf("prog1 is done!\n");
    // sched_stat();
    exit(0);
        
}