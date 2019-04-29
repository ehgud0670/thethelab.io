void check(int signum){
  int signum;
  while(waitpid(0,&status, WNOHANG) >0){
    printf("status: %d \n" ,status);
	}
 
}
