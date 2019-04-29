void check(int signum){
   int status;
   while(wait(&status)>0){
     printf("status: %d \n " ,status);
	 }
}
