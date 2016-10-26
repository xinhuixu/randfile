#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

int randint(){
  int *buff = (int *)malloc(4);
  int fd = open("/dev/random", O_RDONLY);
  read(fd,buff,4);
  int ret = *buff;
  free(buff);
  return ret;
}

int main(){
  umask(0000);

  printf("output.txt\n");
  int rands [10];
  int i;
  for (i = 0; i<10; i++){
    int r = randint();
    rands[i] = r;
    printf("%d: %d\n",i,r);
  }

  int fd = open("output.txt",O_CREAT|O_RDWR,0777);
  printf("writing . . . \n");
  for (i = 0; i<10; i++){
      write(fd, rands + i, 4);
  }
  printf("reading . . . \n");
  fd = open("output.txt",O_RDONLY);
  int *buff = (int *)malloc(4);
  for (i = 0; i < 10; i++){
    read(fd, buff, 4);
    printf("%d: %d\n", i, *buff);
  }
  
  
  close(fd);
  return 0;
}

