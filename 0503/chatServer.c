#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <unistd.h>

# define PCOUNT 1024
int n=0;
int clients[PCOUNT];

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *on_client(void *arg){

  int sock = (intptr_t)arg;
  int pos;

  int j;
  for(j=0;j<PCOUNT; j++){
    if(clients[j] == 0){
      break;
		}
	}
	pos=j;
	clients[j] = sock;

  pthread_mutex_lock(&mutex);
  n++; 
  pthread_mutex_unlock(&mutex);

  while(1){
    char buf[128];
    int ret = read(sock, buf, sizeof buf);
    if(ret<=0){
      break;
		}

    pthread_mutex_lock(&mutex);
    int i;
		for(i=0; i<n; i++){
      write(clients[i],buf,ret);
		}
		pthread_mutex_unlock(&mutex);

	}
  
  clients[pos] = 0;
  
  pthread_mutex_lock(&mutex);
  n--;
  pthread_mutex_unlock(&mutex);
  
  close(sock);
  return 0;
}

int main(){

	int sd = socket(PF_INET, SOCK_STREAM, 0);
	if( sd == -1){
		perror("socket");
		return 1;
	}

	struct sockaddr_in saddr = {0,};
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = INADDR_ANY;
	saddr.sin_port = htons(5001); // little Endian -> big Endian
  bind(sd, (struct sockaddr*)&saddr, sizeof saddr);

	listen(sd, SOMAXCONN);

	struct sockaddr_in caddr = {0,};
	socklen_t caddrlen = sizeof caddr;

	while(1){
		int sock = accept(sd, (struct sockaddr *)&caddr, &caddrlen);
		intptr_t arg = sock;

		printf("%s\n", inet_ntoa(caddr.sin_addr));

		pthread_t thread;
		pthread_create(&thread , NULL , on_client, (void*)arg);
		pthread_detach(thread);
	}
  
  return 0;
}
