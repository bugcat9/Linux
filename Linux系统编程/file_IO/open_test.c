#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>

int main(){
	int fd;
	fd = open("./test.txt",O_CREAT);
	printf("fd = %d ,errno = %d,%s\n",fd,errno,strerror(errno));
	close(fd);
	return 0;
}

