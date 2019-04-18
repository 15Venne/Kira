#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<time.h>
#include<sys/time.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<pthread.h>
#include<sys/epoll.h>
#include<grp.h>
#include<pwd.h>
#include<dirent.h>
#include<errno.h>
#include<sys/wait.h>
#include<signal.h>
#include<sys/uio.h>
#include<mysql/mysql.h>
#include<pthread.h>

#define MYIP "192.168.5.215"
#define MYPORT 2015 //默认端口2015
#define CHILDNUM 5  //默认子进程5
#define QUECAPACITY 10
typedef struct train
{
    int dataLen;
    char buf[1000];
}train;

typedef struct fdArrNode
{
    int *fd;
    int fdMax;
    int fdcnt;
}fdArrNode,*pfdArrNode;

typedef struct threadNode
{
    int *new_fd; //new_fd数组首地址
    int fdMax;   //当前数组最大个数
    int fdcnt;     //new_fd数组个数
    int fds[2];  //pipe
    int cur;
    fdArrNode ouroboros[15];
}threadNode,*pthreadNode;

typedef struct questNode
{
    int new_fd;
    struct questNode *pnext;
}questNode,*pquestNode;

typedef struct nodeQueue
{
    pquestNode phead;
    pquestNode ptail;
    int qCapacity;
    int size;
    pthread_mutex_t mutex;
}nodeQueue,*pnodeQueue;

typedef struct Factory
{
    pthread_t *pthid;
    int threadNum;
    pthread_cond_t cond;
    pnodeQueue pQue;
    short startFlags;
}Factory,*pFactory;

int tcpInit(int*, char*, int);

void factoryInit(pFactory, int, int);
void queInit(pnodeQueue, int);
void factoryStart(pFactory);
void *threadQuest(void*); //子线程
int toMission(int); //子线程主体
void questNodeInsert(pnodeQueue, pquestNode);
int getQuestNode(pnodeQueue, pquestNode*);

//数据库
int getCiphertext(char*, char*);
int insertTable_userToken(char*, char*);
int deleteTable_userToken(char*);
int checkToken(char*);
int insertTable_ConnectInfo(char*);
int GenerateStr(char*);

