#include "user/thread.c"

struct lock_t *lk;
static int max_turns;
static int thread_cnt;
static int curr_turn = 0;
void* pass_frisbee();

int main ( int argc , char * argv []){
	thread_cnt = atoi(argv[1]); //thread count
	max_turns = atoi(argv[2]); //number of max_turns
	
	lock_init(lk);

    int i = 1;
    for(uint64 i = 1; i <= thread_cnt; i++){
        thread_create(pass_frisbee, (void *)&i);
    }

    exit(0);
}

void* pass_frisbee(void *arg){
	int t_id = (uint64)arg; //thread ID
    
	while(max_turns > curr_turn){
		lock_acquire(lk);

		if(max_turns == curr_turn) break;
		
        if(curr_turn == t_id){
            printf("Pass number no: %d, Thread %d is passing the token to thread", curr_turn, t_id);
            t_id = (t_id + 1) % thread_cnt;
			printf(" %d\n", t_id);
			
            curr_turn++;
			
            lock_release(lk);
		 	sleep(1);
		}
		else
		{
			lock_release(lk);
			sleep(1);
		}
	}
	
	exit(0);
}