#include <stdio.h>
#include <unistd.h> //read(),write()
#include <sys/types.h> //socket()
#include <sys/socket.h>
#include <netinet/in.h> // inet_addr()
#include <arpa/inet.h> // htons() inet_addr()
#include <pthread.h>

void *on_client(void *arg){
  
  intptr_t sock = (intptr_t)arg;

  char buf[128];
  int ret;
  while(1){
    ret = read(sock, buf, sizeof buf);
    if(ret<=0)
    	break;

    write(1,buf,ret);

	}
}


int main(){

  int sock = socket(PF_INET, SOCK_STREAM, 0);
  if(sock == -1){
    perror("sock");
    return 1;
	}

  struct sockaddr_in caddr = {0, };
  caddr.sin_family = AF_INET;
  caddr.sin_addr.s_addr = inet_addr("127.0.1.1");
  caddr.sin_port = htons(5001); // little => big

  if(connect(sock, (struct sockaddr *)&caddr,sizeof caddr) == -1){
    perror("connect");
    return 1;
	}
  
  pthread_t thread;
  intptr_t arg = sock;
  pthread_create(&thread, NULL, on_client,(void*)arg);
  pthread_detach(thread);

  char buf[128];
  int ret;
  while(1){
    ret = read(0, buf, sizeof buf);
    if(ret <=0)
    	break;
    write(sock, buf, ret);
    
	}

  return 0;
}
