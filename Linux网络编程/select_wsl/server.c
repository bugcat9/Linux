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

    int server_sockfd, client_sockfd;
    int server_len, client_len;
    int fd_max, n;
    char buf[BUF_SIZE], str[INET_ADDRSTRLEN];
    // c中结构体使用，必须加struct
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    int result;
    fd_set readfds, tempfds;
    //创建 服务器端 socket
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    //准备地址
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(atoi(argv[1]));
    server_len = sizeof(server_address);
    //设置绑定和监听
    if (bind(server_sockfd, (struct sockaddr *)&server_address, server_len) == -1)
    {
        error_handling("bind error");
    }

    if (listen(server_sockfd, 128) == -1)
    {
        error_handling("listen error");
    }

    printf("server waiting\n");
    FD_ZERO(&readfds);
    FD_SET(server_sockfd, &readfds); //将服务器端socket 监听描述符加入到集合中
    fd_max = server_sockfd;

    struct timeval timeout;
    while (1)
    {
        //将需要监听的描述符复制给 tempfds
        tempfds = readfds;
        // select第二个参数是传入传出参数，所以开始才需要复制
        
        // 情况1.设置timeout的等待时间
        timeout.tv_sec = 3;
        timeout.tv_usec = 0;
        // (fd_set)*0 和 NULL 用法相同
        // result = select(fd_max + 1, &tempfds, NULL, NULL, &timeout);
        // result = select(fd_max + 1, &tempfds, (fd_set *)0, (fd_set *)0, &timeout);
        
        //情况2.设置select 阻塞的情况
        result = select(fd_max + 1, &tempfds, (fd_set *)0, (fd_set *)0, (struct timeval *)0);
        printf("-------next--------\n");
        
        if (result < 0)
        {
            error_handling("select error");
            break;
        }

        for (size_t fd = 0; fd < fd_max + 1; fd++)
        {
            //寻找到相关文件描述符
            if (FD_ISSET(fd, &tempfds))
            {
                //判断是否是监听文件描述符
                if (fd == server_sockfd)
                {
                    client_len = sizeof(client_address);
                    client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
                    printf("received from %s at PORT %d on fd %d\n", inet_ntop(AF_INET, &client_address.sin_addr, str, sizeof(str)),
                           ntohs(client_address.sin_port), client_sockfd);
                    //新的文件描述符加入读中
                    FD_SET(client_sockfd, &readfds);
                    if (fd_max < client_sockfd)
                        fd_max = client_sockfd;
                }
                else
                {
                    //说明是读描述数
                    if ((n = read(fd, buf, sizeof(buf))) == 0)
                    { /* 当client关闭链接时,服务器端也关闭对应链接 */
                        close(fd);
                        FD_CLR(fd, &readfds); /* 解除select对此文件描述符的监控 */
                    }
                    else if (n > 0)
                    {

                        for (size_t j = 0; j < n; j++)
                            buf[j] = toupper(buf[j]);
                        write(fd, buf, n);
                        write(STDOUT_FILENO, buf, n);
                    }
                }
            }
        }
    }
    close(server_sockfd);
    printf("--------------------server finish!");
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}