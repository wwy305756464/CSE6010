#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef int ElementType;

#define SUCCESS 0
#define FAILURE 1
#define FALSE 0
#define TRUE 1
#define MAX_SIZE 10

typedef struct _node{
    int value;
    int visited;
    struct _node *next;
}Node, *link;

typedef struct _mazelink {
    int vertex;
    int edge;
    link list;
}Mazelink, *MLL;

typedef struct ConstructQueue
{
    int front; 
    int rear;  
    ElementType queueArr[MAX_SIZE];
}ConstructQueue;

int** matrix_allocate(int row_num, int col_num);
void modify_matrix(int **matrix, int rownum, int colnum);
void zeroout_matrix(int **matrix, int rownum, int colnum);
Node* create_node(int v);
MLL initial_maze(int vs[], int size);
int find_index(int v, link list, int n);
int add_edge(int start, int end, MLL m);
void print_maze(MLL m);

int queue_is_empty(ConstructQueue *queue);
int queue_delete(ConstructQueue *queue,ElementType *value);
int queue_insert(ConstructQueue *queue,ElementType value);
int queue_pop(ConstructQueue *queue,ElementType *value);
