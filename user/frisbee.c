#include "user/thread.c"

struct lock_t lk;
static int max_turns;
static int thread_cnt;
static int curr_turn = 1;
int thrower;
void pass_frisbee();

int main ( int argc , char * argv []){
	thread_cnt = atoi(argv[1]); //thread count
	max_turns = atoi(argv[2]); //number of max_turns
	
	lock_init(&lk);
	printf("max turn = %d\n", max_turns);
	printf("thread count = %d\n", thread_cnt);
    for(uint64 i = 0; i < thread_cnt; i++){
    	thread_create((void*)pass_frisbee, (void*)&i);
    }
	while(wait(0) >= 0){
		sleep(1);
	};
	// exit(0);
	return 0;
}

void pass_frisbee(void *arg){
	int t_id = *(int*)arg; //thread ID
	while(curr_turn <= max_turns){
		lock_acquire(&lk);
		// printf("curr_turn = %d from %d\n", curr_turn, t_id);
		// printf("It's %d's turn from %d\n", (curr_turn-1)%thread_cnt, t_id);
		if(((curr_turn-1) % thread_cnt) == t_id){
            printf("Pass number no: %d, Thread %d is passing the token to thread", curr_turn, t_id);
            t_id = (t_id + 1) % thread_cnt;
			printf(" %d\n", t_id);
            curr_turn++;
		}
		lock_release(&lk);
	}
	exit(0);
}