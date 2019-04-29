# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>

int main(){
	int fd;
	char buf[BUFSIZ];
	ssize_t nr;

	fd = open("hello.txt", O_RDONLY, O_NONBLOCK);
	if(fd == -1){
		perror("file");
	}

	nr = read(fd,buf,BUFSIZ);
	if(nr == -1){
		if(errno == EAGAIN){
			printf("not read!\n");
			sleep(10);
			nr = read(fd,buf,BUFSIZ);
			if(nr == -1){
				perror("read");
			}
		}
		else{
      perror("read");
		}
	}
  
  printf("hello.txt: %s\n", buf);

	return 0;
}
