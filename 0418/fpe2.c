#include <stdio.h>
#include <signal.h>

void foo(int signum){

printf("signum:%d\n",signum);

}

int main() {

  signal(SIGFPE, foo);
	double n = 10/0;

	return 0;
}
