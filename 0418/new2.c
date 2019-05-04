#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

// 자식 프로세스는 자신이 종료될 때, 부모 프로세스에게 SIGCHLD 시그널을 전달한다.
void foo(int signum) {
	printf("자식 죽음...\n");

	int status;
	wait(&status);
	printf("status: %d\n", status);

}

int main() {
	signal(SIGCHLD, foo);
	int i;
	pid_t pid;
	int j;

	for(j=0;j<20;++j){
		pid =	fork();
		if (pid == 0) { // 자식 프로세스
			for (i = 0; i < 3; ++i) {
				printf("child process..\n");
				if(j>5)
					sleep(1);
			}
			exit(0);

		} 
	}
	// fork()가 반환될 때, 자식 프로세스도 fork() 함수를 반환한다.


	for (i = 0; i < 30; ++i) {
		printf("parent process..%d\n",i);
		sleep(1);
	}
	exit(0);
}

