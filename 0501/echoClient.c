#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(){

  int sock = socket(PF_INET, SOCK_STREAM, 0);
  if(sock == -1){
    perror("socket");
    return 1;
	}
  
  struct sockaddr_in caddr = {0, };
  caddr.sin_family = AF_INET;
  caddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  caddr.sin_port = htons(5000);
  if(connect(sock, (struct sockaddr*)&caddr, sizeof caddr ) == -1){
    perror("connect");
    return 1;
	}
// stdin 0   
// stdout 1
// stderr 2
// number is file descriptor
	char buf[128];
	while(1){
    int ret = read(0, buf, sizeof buf);
    write(sock, buf, ret);

    ret = read(sock, buf, sizeof buf);
    if(ret<=0) //EOF = 0
      break;

    write(1,buf,ret);
	}
	return 0;
}
