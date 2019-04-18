#include"head.h"

int getQuestNode(pnodeQueue pq, pquestNode *pn)
{
    if(0 == pq->size)
    {
        return -1;
    }
    else
    {
        *pn = pq->phead;
        pq->phead = pq->phead->pnext;
        pq->size--;
        if(0 == pq->size)
        {
            pq->ptail = NULL;
        }
        return 0;
    }
}

void *threadQuest(void *p)
{
    pFactory pf = (pFactory)p;
    pquestNode pcur;
    int ret;
    while(1)
    {
        pthread_mutex_lock(&pf->pQue->mutex);
        if(pf->pQue->size != 0)
        {   
            pthread_cond_wait(&pf->cond, &pf->pQue->mutex);
        }
        ret = getQuestNode(pf->pQue, &pcur);
        pthread_mutex_unlock(&pf->pQue->mutex);
        if(-1 == ret)
        { continue; }
        else
        {
            ret = toMission(pcur->new_fd);
            //printf("客户端已退出\n");
            close(pcur->new_fd);
            free(pcur);
            pcur = NULL;
        }
    }
}
