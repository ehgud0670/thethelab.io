# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>

int main(){
  int fd;
  
  fd = creat("hello.txt", 0644);

  const char *buf = "My name is Doehyung!";
  ssize_t nr;

  nr = write(fd,buf, strlen(buf));
  if(nr == -1){
    perror("file");
	}


  return 0;
}
