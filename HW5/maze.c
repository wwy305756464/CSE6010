#include "maze.h"



Node* create_node(int v){
    Node *newnode = (Node*)malloc(sizeof(Node));
    newnode->value = v;
    newnode->next = NULL;
    return newnode;
}

MLL initial_maze(int vs[], int size){
    int n = size;
    MLL m = (MLL)malloc(sizeof(Mazelink));
    m->vertex = n;
    m->edge = 0;
    m->list = (link)malloc(sizeof(Node)*n);
    for(int i = 0; i < n; ++i){
        m->list[i].value = vs[i];
        m->list[i].next = NULL;
    }
    return m;
}

int find_index(int v, link list, int n){
    for(int i = 0; i < n; ++i){
        if(list[i].value == v){
            return i;
        }
    }
    return -1;
}

int add_edge(int start, int end, MLL m){
    link list = m->list;
    int from = find_index(start, list, m->vertex), to = find_index(end, list, m->vertex);
    if(start == -1 || end == -1 || start == end){
        return 0;
    }
    Node* add_node = create_node(end);
    add_node->next = list[from].next;
    list[from].next = add_node;
    ++m->edge;
    return 1;
}

void print_maze(MLL m){
    int n = m->vertex;
    for(int i = 0; i < n; ++i){
        Node *tmp = &(m->list[i]);
        while(tmp){
            printf("%d-->", tmp->value);
            tmp = tmp->next;
        }    
        printf("NULL\n");
    }
}

// void file_write(MLL m, int row_num, int col_num, int start_point, int end_point){

// }






int** matrix_allocate(int row_num, int col_num) {
    int ** matrix = NULL;
	if(row_num <= 0 || col_num <= 0) {
		printf("ERROR: Invalid input size when creating matrix\n");
		return NULL;
	}

	matrix = (int **) malloc(row_num * sizeof(int*));
	if(matrix == NULL) {
		printf("ERROR: Memory allocation failed\n");
	}

	for(int i = 0; i < row_num; i++) {
		matrix[i] = (int *) malloc(col_num * sizeof(int));
		if(matrix[i] == NULL) {
			printf("ERROR: Memory allocation for matrix failed\n");
			return NULL;
		}
	}

	return matrix;
}

void modify_matrix(int **matrix, int rownum, int colnum){
    if(matrix == NULL){
        printf("ERROR: The Input matrix is NULL\n");
    }
    int num = 0;
    for(int i = 0; i < rownum; ++i){
        for(int j = 0; j < colnum; ++j){
            matrix[i][j] = num++;
        }
    }
    return;
}

void zeroout_matrix(int **matrix, int rownum, int colnum){
    if(matrix == NULL){
        printf("ERROR: The Input matrix is NULL\n");
    }
    for(int i = 0; i < rownum; ++i){
        for(int j = 0; j < colnum; ++j){
            matrix[i][j] = 0;
        }
    }
    return;
}

