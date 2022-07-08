#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>


void sys_err(const char *str)
{
    perror(str);
    exit(1);
}


int main(){

    pid_t pid;
    char buf[1024];
    int fd[2];
    char *p = "test for pipe\n";
    
   if(pipe(fd) == -1) 
       sys_err("pipe");

   pid = fork();
   
    if (pid < 0) {
       sys_err("fork err");
    } else if (pid == 0) {
        //子进程
	close(fd[1]); //关闭写端
        int len = read(fd[0], buf, sizeof(buf));
        write(STDOUT_FILENO, buf, len);
        close(fd[0]);
   } else {
	//父进程
       close(fd[0]);	//关闭读端
       write(fd[1], p, strlen(p));
       wait(NULL);
       close(fd[1]);
   }
    
    return 0;

}
