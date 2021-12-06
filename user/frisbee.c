#include "user/thread.c"

struct lock_t lk;
static int max_turns;
static int thread_cnt;
static int curr_turn = 1;
void pass_frisbee();

int main ( int argc , char * argv []){
	thread_cnt = atoi(argv[1]); //thread count
	max_turns = atoi(argv[2]); //number of max_turns
	
	lock_init(&lk);
    for(uint64 i = 0; i < thread_cnt; i++){
    	thread_create((void*)pass_frisbee, (void*)&i);
		sleep(10);
    }
	//wait children threads to exit()
	while(wait(0) >= 0);
	printf("Simulation of Frisbee game has finished, %d round were palyed in total\n", max_turns);
	exit(0);
}

void pass_frisbee(void *arg){
	int t_id = *(int*)arg; //thread ID
	while(curr_turn <= max_turns){
		lock_acquire(&lk);
		// check if it's this thread's turn, if so, pass, othterwise, directly give up the lock.
		if(((curr_turn-1) % thread_cnt) == t_id){
            printf("Pass number no: %d, Thread %d is passing the token to thread", curr_turn, t_id);
			printf(" %d\n", (t_id + 1) % thread_cnt);
            curr_turn++;
		}
		lock_release(&lk);
	}
	exit(0);
}