#include <stdio.h>
#include "assignment2.h"

int main() {
    LLQueue *LLQ;
    LLQueue *emptyLLQ;

    // test creating a queue, first insert 50 into the empty queue, then continully insert
    // 34.24, 66, 22.6 and 59. Now queue has 5 items, so instert 99.99. Each step would be tested
    // with LLQ_count() and LLQ_print(). Also the final queue would be print for further use. 
    create_insert_test(LLQ, 50, 34.24, 66, 22.6, 99.99, 63);

    // test returing the maximum and the minimum value of a queue containing at least 4 elements
    max_min_test(LLQ);

    // test searching for an item present at the beginnin, middle and end of the linked lis
    search_test(LLQ, 50, 66, 63, 453);

    delete_test(LLQ, emptyLLQ);

    free_test(LLQ, emptyLLQ);

    

}