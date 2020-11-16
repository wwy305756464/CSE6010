//arrayQueue.c
#include "maze.h"
#include <stdio.h>
#include <string.h>


int queue_is_empty(ConstructQueue *queue)
{
    if((queue->rear + 1) % MAX_SIZE == queue->front)
    {
        return TRUE;
    }
    else 
        return FALSE;
}


int queue_delete(ConstructQueue *queue,ElementType *value)
{
    if(queue_is_empty(queue))
        return FAILURE;
    
    *value = queue->queueArr[queue->front];
    queue->front = (queue->front + 1) % MAX_SIZE;
    return SUCCESS;
}

int queue_pop(ConstructQueue *queue,ElementType *value)
{
    if(queue_is_empty(queue))
        return FAILURE;
    
    *value = queue->queueArr[queue->front];
    return *value;
}


int queue_insert(ConstructQueue *queue,ElementType value)
{
    queue->rear = (queue->rear + 1) % MAX_SIZE;
    queue->queueArr[queue->rear] = value;
    return SUCCESS;
}
