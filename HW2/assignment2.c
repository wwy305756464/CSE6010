#include "assignment2.h"
#include <limits.h>

#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

// create a new queue and return a pointer to it
LLQueue* LLQ_create() {
    LLQueue* head = malloc(sizeof(LLQueue));
    if (head == NULL) {
        printf("Error! Cannot create linked list since lacking of memory");
        return NULL;
    }

    head -> val = -1;
    head -> next = NULL;

    printf("Successfuly create a new queue! \n");
    return head;
}


// insert a double data into queue LLQ
// return 0 if success, return arbitrary value not 0 if it fails
int LLQ_insert(LLQueue *LLQ, double data) {
    // if NULL, return -1
    if(LLQ == NULL) {
        printf("Error! Invalid linked list queue. \n");
        return -1;
    }

    LLQueue *newnode; // pointer of the new node
    LLQueue *prenode = LLQ;
    newnode = (LLQueue *) malloc(sizeof(LLQueue)); // memory for new node

    newnode -> val = data;
    newnode -> next = NULL;

    while(prenode -> next != NULL) {
        prenode = prenode -> next;
    }

    newnode -> next = prenode -> next;
    prenode -> next = newnode;

    return 0;
}

// remove the oldest data from the queue LLQ
double LLQ_delete(LLQueue *LLQ){ 

    if (LLQ == NULL || LLQ -> next == NULL) {
        printf("Error! Invalid linked list queue. \n");
        return 0.0;
    }
    LLQueue *prenode = LLQ;
    prenode = prenode -> next;
    double value = prenode -> val;
    free(prenode);
    LLQ -> next = prenode -> next;
    // prenode = prenode -> next;

    return value;
}


// search for value data within the queue, return a pointer to the item
double* LLQ_Search(LLQueue *LLQ, double data){
    if (LLQ == NULL) {
        printf("Error! Invalid linked list queue. \n");
    }
    double *ptr;
    LLQueue *prenode = LLQ;
    prenode = prenode -> next;
    LLQueue *dummyHead = LLQ;

    while (prenode != NULL) {
        
        if(prenode -> val == data) {
            ptr = &prenode -> val;
            return ptr;
        }

        prenode = prenode -> next;
    }
    LLQ = dummyHead;
    return NULL;
}


// return the minimum of the items in the queue
double LLQ_minimum(LLQueue *LLQ){
    if (LLQ == NULL) {
        printf("Error! Invalid linked list queue. \n");
        return INT_MAX;
    }
    LLQueue *prenode = LLQ;
    double minval = INT_MAX;

    while(prenode -> next != NULL) {
        LLQueue *tempnode = prenode -> next;
        minval = min(minval, tempnode -> val); 
        prenode = prenode -> next;
    }

    return minval;
}


// return the maximum of the items in the queue
double LLQ_maximum(LLQueue *LLQ){
    if (LLQ == NULL) {
        printf("Error! Invalid linked list queue. \n");
        return INT_MAX;
    }

    LLQueue *prenode = LLQ;
    double minval = INT_MIN;

    while(prenode -> next != NULL) {
        LLQueue *tempnode = prenode -> next;
        minval = max(minval, tempnode -> val); 
        prenode = prenode -> next;
    }

    return minval;
}


// return number of items currently in the queue
unsigned int LLQ_count(LLQueue *LLQ){
    if (LLQ == NULL) {
        printf("Error! Invalid linked list queue. \n");
        return 0;
    }

    LLQueue *prenode = LLQ;
    unsigned int cnt = 0;

    while(prenode -> next != NULL) {
        cnt += 1;
        prenode = prenode -> next;
    }
    
    return cnt;
}


// print the data items stored in the queue in order from oldest to newest without 
// changing the contents of the queue
// FIXME: 想修改成链表的形式，但是怎么省略掉最后一个 -> ？
void LLQ_print(LLQueue *LLQ){
        LLQ = LLQ -> next;
    double val;

    if(LLQ == NULL){
        printf("The linked list queue is empty");
    }

    while(LLQ!=NULL) {

        val = LLQ -> val;
        // printf("%.2f ->", val);
        printf("%.2f  ", val);
        LLQ = LLQ -> next;
    }
    
    printf("\n");
}


// delete the queue LLQ by releasing all memory used by the data structure
void LLQ_free(LLQueue *LLQ){
    if (LLQ == NULL) {
        printf("Error! Invalid linked list queue. \n");
    }
    
	LLQueue* prenode;

	while(LLQ != NULL){
		prenode = LLQ;
		LLQ = LLQ -> next;
		free(prenode);
	}
	free(prenode);

}
