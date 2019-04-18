#include"head.h"

void titleprint()
{
    printf("---------------------------------------------------------\n");
}

void toJoin(int socketFd)
{
    int dataLen, fd;
    char buf[200]={0};
    system("clear");
    titleprint();
    printf("\n\n\n\n                      User:"); fflush(stdout);
    scanf("%s", buf);
    dataLen = strlen(buf);
    send(socketFd, (char*)&dataLen, 4, 0); //发送用户名
    send(socketFd, buf, dataLen, 0);
    
    memset(buf, 0, sizeof(buf));
    recv(socketFd, (char*)&dataLen, 4, 0);//接收盐值
    recv(socketFd, buf, dataLen, 0);
    printf("盐值:%s\n", buf);
    while(1)
    {
        memset(buf, 0, sizeof(buf));
        recv(socketFd, buf, 4, 0);
    }
}
