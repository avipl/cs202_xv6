#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){

    //assign ticket to this program
    int ticket = 40;
    assign(ticket);
    // char* name = "prog2";
    // assign(ticket, "prog2");
    
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

    printf("prog2 is done!\n");
    exit(0);
        
}