#ifndef assignment2_h
#define assignment2_h

#include<stdio.h>
#include<sys/malloc.h>
#include<stdlib.h>

// TODO: cmakelist

// use typedef to fefine the structure LLQueue to represent linked-list queue
typedef struct LLQueue{
    double value;
    struct LLQueue *next;
} LLQueue;


// create a new queue and return a pointer to it
LLQueue *LLQ_create(void);

// insert a double data into queue LLQ
int LLQ_insert(LLQueue *LLQ, double data);

// remove the oldest data from the queue LLQ
double LLQ_delete(LLQueue *LLQ);

// search for value data within the queue, return a pointer to the item
double *LLQ_Search(LLQueue *LLQ, double data);

// return the minimum of the items in the queue
double LLQ_minimum(LLQueue *LLQ);

// return the maximum of the items in the queue
double LLQ_maximum(LLQueue *LLQ);

// return number of items currently in the queue
unsigned int LLQ_count(LLQueue *LLQ);

// print the data items stored in the queue in order from oldest to newest without 
// changing the contents of the queue
void LLQ_print(LLQueue *LLQ);

// delete the queue LLQ by releasing all memory used by the data structure
void LLQ_free(LLQueue *LLQ);


// test cases
void create_insert_test(LLQueue* LLQ, double data1, double data2, double data3, double data4, double data5, double data6);
void max_min_test(LLQueue* LLQ);
void search_test(LLQueue* LLQ, double front_ele, double middle_ele, double end_ele, double not_present_ele);
void delete_test(LLQueue* LLQ, LLQueue* emptyLLQ);

#endif