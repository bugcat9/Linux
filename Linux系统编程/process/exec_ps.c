#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

int main(){
	int fd;
	fd = open("ps.out",O_WRONLY|O_CREAT|O_TRUNC,0644);
	if(fd<0){
		perror("open ps error");
		exit(1);
	}
	
	dup2(fd,STDOUT_FILENO);
	execlp("ps","ps","aux",NULL);
	close(fd);
	return 0;
}
