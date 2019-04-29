# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>

# define FALSE 0
# define TRUE 1

__thread int flag = FALSE;
int global=0; 

void *random_game(void *arg){
	flag= rand()%2; 
  global++;	
  sleep(1);
  if(flag){
    printf("꽝이 아니네요 flag: %d\n", flag);
	}
	else{
		printf("땡! 당신은 꽝입니다! flag: %d\n", flag);
	}

	printf("global: %d \n\n", global);
}


int main(){
	int i;
	pthread_t thread[4];

	for(i=0; i<4; i++){
		pthread_create(thread+i, NULL, random_game, NULL); 
	}

	for(i=0; i<4; i++){
		pthread_join(thread[i], NULL);
	}


	return 0; 
}
