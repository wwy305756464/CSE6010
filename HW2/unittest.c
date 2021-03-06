#include <stdio.h>
#include "assignment2.h"

void create_insert_test(LLQueue* LLQ, double data1, double data2, double data3, double data4, double data5, double data6) {
    printf("--------------------- CREATE AND INSERT TEST ----------------------- \n");

    printf("Test create a new queue: \n");
    LLQ = LLQ_create();
    printf("\n");

    printf("Test insert an item into an empty queue: \n");
    printf("Before inserting, the queue is: ");
    LLQ_print(LLQ);
    printf("And number of elements in this case is: %d. \n", LLQ_count(LLQ));
    
    LLQ_insert(LLQ, data1);
    printf("After inserting, the queue is: ");
    LLQ_print(LLQ);
    printf("And number of elements in this case is: %d. \n\n", LLQ_count(LLQ));
    
    LLQ_insert(LLQ, data2);
    LLQ_insert(LLQ, data3);
    LLQ_insert(LLQ, data4);
    LLQ_insert(LLQ, data5);    
    printf("Test insert an item into a queue containing at least 4 elements: \n");
    printf("Before inserting, the queue is: ");
    LLQ_print(LLQ);
    printf("And number of elements in this case is: %d. \n", LLQ_count(LLQ));
    LLQ_insert(LLQ, data6);
    printf("After inserting, the queue is: ");
    LLQ_print(LLQ);
    printf("And number of elements in this case is: %d. \n\n", LLQ_count(LLQ));

    // double* ptr;
    // LLQueue* prenode = LLQ;
    // ptr = &prenode -> val;
    // return ptr;

}

void max_min_test(LLQueue* LLQ) {
    printf("-------------------------- MAX AND MIN TEST --------------------------- \n");
    LLQ = LLQ_create();
    LLQ_insert(LLQ, 50);
    LLQ_insert(LLQ, 34.24);
    LLQ_insert(LLQ, 66);
    LLQ_insert(LLQ, 22.6);
    LLQ_insert(LLQ, 99.99);
    LLQ_insert(LLQ, 63);

    printf("The original queue is: \n");
    LLQ_print(LLQ);
    double min = LLQ_minimum(LLQ);
    printf("min value is: %.2f \n", min);

    double max = LLQ_maximum(LLQ);
    printf("max value is: %.2f \n\n", max);

}


void search_test(LLQueue* LLQ, double front_ele, double middle_ele, double end_ele, double not_present_ele) {
    printf("------------------------------ SEARCH TEST ---------------------------- \n");
    LLQ = LLQ_create();
    LLQ_insert(LLQ, 50);
    LLQ_insert(LLQ, 34.24);
    LLQ_insert(LLQ, 66);
    LLQ_insert(LLQ, 22.6);
    LLQ_insert(LLQ, 99.99);
    LLQ_insert(LLQ, 63);
    LLQ_print(LLQ);
    double * ptr1 = LLQ_Search(LLQ, front_ele);
    printf("search result for front element is: %p \n", ptr1);

    double * ptr2 = LLQ_Search(LLQ, middle_ele);
    printf("search result for middle element is: %p \n", ptr2);

    double * ptr3 = LLQ_Search(LLQ, end_ele);
    printf("search result for end element is: %p \n", ptr3);

    double * ptr4 = LLQ_Search(LLQ, not_present_ele);
    printf("search result for not present element is: %p \n", ptr4);

    printf("\n");
}


void delete_test(LLQueue* LLQ, LLQueue* emptyLLQ) {
    printf("--------------------------- DELETE TEST ------------------------------ \n");
    LLQ = LLQ_create();
    LLQ_insert(LLQ, 50);
    LLQ_insert(LLQ, 34.24);
    LLQ_insert(LLQ, 66);
    LLQ_insert(LLQ, 22.6);
    LLQ_insert(LLQ, 99.99);
    LLQ_insert(LLQ, 63);
    

    unsigned int LLQlength = LLQ_count(LLQ);
    printf("Deleting all items in a queue one after the other: \nThe original queue is: \n");
    LLQ_print(LLQ);
    for (int i = 0; i < LLQlength; ++i){
        double deleted_node = LLQ_delete(LLQ);
        printf("%d's deleted node is: %.2f \n", i+1, deleted_node);
        printf("linked list now is: ");
        LLQ_print(LLQ);
    }

    printf("\nNow if the queue is empty: \n");

    emptyLLQ = LLQ_create();
    LLQ_print(emptyLLQ);

    double deleted_node_empty = LLQ_delete(emptyLLQ);
    printf("deleted node is: %.2f \n", deleted_node_empty);
    printf("linked list now is: ");
    LLQ_print(emptyLLQ);
}

void free_test(LLQueue* LLQ, LLQueue* emptyLLQ) {
    printf("\n--------------------------- FREE TEST ------------------------------ \n");
    LLQ = LLQ_create();
    LLQ_insert(LLQ, 50);
    LLQ_insert(LLQ, 34.24);
    LLQ_insert(LLQ, 66);
    LLQ_insert(LLQ, 22.6);
    LLQ_insert(LLQ, 99.99);
    LLQ_insert(LLQ, 63);

    printf("Before free up the queue, the LLQ is: ");
    LLQ_print(LLQ);
    LLQ_free(LLQ);

    printf("\nNow if the input queue is empty: \n");

    emptyLLQ = LLQ_create();
    printf("Before free up the queue, the LLQ is: ");
    LLQ_print(emptyLLQ);
    LLQ_free(emptyLLQ);
}
