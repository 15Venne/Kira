#include"head.h"

int main()
{
    int socketFd;
    struct sockaddr_in serAddr;
    int ret;
Loop:
    socketFd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serAddr, 0, sizeof(serAddr));
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(SERVERPORT);
    serAddr.sin_addr.s_addr = inet_addr(SERVERIP);
    
    ret = connect(socketFd, (struct sockaddr*)&serAddr, sizeof(serAddr));
    if(-1 == ret)
    {
        perror("connect");
        sleep(3);
        goto Loop;
    }
    printf("服务器已连接__\n");
    toJoin(socketFd);
    return 0;
}
