#include"head.h"

void factoryStart(pFactory pf)
{
    int i;
    if(0 == pf->startFlags)
    {
        for(i = 0;i < pf->threadNum; ++i )
        {
            pthread_create(&pf->pthid[i], NULL, threadQuest, pf);
        }
    }
}

void queInit(pnodeQueue pq, int qCapacity)
{
    memset(pq, 0, sizeof(nodeQueue));
    pq->qCapacity = qCapacity;
    pthread_mutex_init(&pq->mutex, NULL);
}

void factoryInit(pFactory pf, int threadNum, int qCapacity)
{
    memset(pf, 0, sizeof(Factory));
    pf->pthid = (pthread_t*)calloc(threadNum, sizeof(pthread_t));
    pf->threadNum = threadNum;
    pf->pQue = (pnodeQueue)calloc(1, sizeof(nodeQueue));
    queInit(pf->pQue, qCapacity);
}
