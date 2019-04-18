#include"head.h"

int toMission(int new_fd)
{
    int dataLen;
    char buf[200]={0};
    char userName[20]={0};
    recv(new_fd, (char*)&dataLen, 4, 0);
    recv(new_fd, userName, dataLen, 0); // 接收用户名
    printf("收到用户名: %s\n", userName);
    getCiphertext(userName, buf);
    printf("盐值:%s\n", buf);
    dataLen = strlen(buf);
    send(new_fd, (char*)&dataLen, 4, 0);
    send(new_fd, buf, dataLen, 0);
    while(1)
    {
        recv(new_fd, buf, 4, 0);
    }
}
