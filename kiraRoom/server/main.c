#include"head.h"

void questNodeInsert(pnodeQueue pq, pquestNode pnew)
{
    if(NULL == pq->phead )
    {
        pq->phead = pnew;
        pq->ptail = pnew;
    }
    else
    {
        pq->ptail->pnext = pnew;
        pq->ptail = pnew;
    }
    pq->size++;
}


int main()
{
    int ret;
    Factory Fa;
    factoryInit(&Fa, CHILDNUM, QUECAPACITY);
    factoryStart(&Fa);
    int socketFd, new_fd;
    pquestNode pnew;
    ret = tcpInit(&socketFd, MYIP, MYPORT);
    if(-1 == ret)
    { 
        printf("tcpInit failed\n");
        return -1;
    }
    while(1)
    {
        printf("等待连接...\n");
        new_fd = accept(socketFd, NULL, NULL);
        printf("new_fd = %d\n", new_fd);
        pnew = (pquestNode)calloc(1, sizeof(questNode));
        pnew->new_fd = new_fd;
        pthread_mutex_lock(&Fa.pQue->mutex);
        questNodeInsert(Fa.pQue, pnew);
        pthread_mutex_unlock(&Fa.pQue->mutex);
        usleep(1000);
        pthread_cond_signal(&Fa.cond);
    }
    return 0;
}
