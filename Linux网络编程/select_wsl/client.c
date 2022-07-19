#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

void error_handling(char *message);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Invalid port,please check out port");
        exit(1);
    }

    int client_sockfd;
    int len,n;    
    char buf[BUF_SIZE];
    struct sockaddr_in address; //服务器端网络地址结构体
    int result;
    client_sockfd = socket(AF_INET, SOCK_STREAM, 0); //建立客户端socket
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(atoi(argv[1]));
    len = sizeof(address);
    //进行链接
    result = connect(client_sockfd, (struct sockaddr *)&address, len);
    if (result == -1)
    {
        error_handling("connect error");
    }
    printf("------------connect ok----------------\n");
    //从屏幕得到输入字母
    while (fgets(buf, BUF_SIZE, stdin) != NULL) {
        write(client_sockfd, buf, strlen(buf));
        n = read(client_sockfd, buf, BUF_SIZE);
        if (n == 0) {
            printf("the other side has been closed.\n");
            break;
        }
        else
            write(STDOUT_FILENO, buf, n);
    }
    close(client_sockfd);
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}