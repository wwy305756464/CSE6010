#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

int main(int argc, char * argv[]){
	if(argc != 2){
        printf("Please enter correct arguments \n");
        return 1;
    }

	const char *file_name = argv[1];

	int rownum = 0, colnum = 0;
	int ta[2] = {0};
	FILE *fpRead=fopen(file_name,"r");
	if(fpRead==NULL)
	{
		return 0;
	}
	for(int i=0;i<2;i++)
	{
		fscanf(fpRead,"%d ",&ta[i]);
	}
	rownum = ta[0], colnum = ta[1];

	int M = rownum * colnum + 3, N = 4;
	int readin_matrix[M][N];

    for(int i = 0; i < M; ++i){
        for(int j = 0; j < N; ++j){
            readin_matrix[i][j] = -1;
        }
    }

    FILE *fp;
    char *buffer;
    char ret;
    int cnt = 0;
    

    // Open a file ("test.txt")
    if ((fp = fopen(file_name, "r")) == NULL) {
            fprintf(stdout, "Error: Can't open file !\n");
            return -1;
    }
    
	// Alloc buffer size (Set your max line size)
    buffer = malloc(sizeof(char) * 4096);
    while(!feof(fp))
    {
        // Clean buffer
        memset(buffer, 0, 4096);
        // Read a line
        ret = fscanf(fp, "%4095[^\n]\n", buffer);
        if (ret != EOF) {
            // Print line
            int e = 0;
            int fe = 0;
            while(e < sizeof(buffer)){
                if(buffer[e] == '\0'){
                    break;
                }
                int res = 0;
                while(buffer[e] != ' '){
                    res = res * 10 + (buffer[e] - '0');
                    ++e;
                }
                // printf("Line 202 value is: %d \n", res);
                readin_matrix[cnt][fe++] = res;
                ++e;
            }
            ++cnt;
        }
    }
    // Free buffer
    free(buffer);
    // Close file
    fclose(fp);

	int rows = readin_matrix[0][0];
	int cols = readin_matrix[0][1];
	int start = readin_matrix[1][0];
	//int start = 8;
	int end = readin_matrix[1][1];

	int vs[cols * rows];
	for(int i = 0; i < cols * rows; ++i){
        vs[i] = i;
    }
	MLL m = initial_maze(vs, cols * rows);

	for(int i = 2; i < rows * cols + 2; ++i){
		for(int j = 0; j < 4; ++j){
			if(readin_matrix[i][j] != -1){
				add_edge(i - 2, readin_matrix[i][j], m);
			}
		}
	}

	//print_maze(m);

	int queue_visited[rows * cols];
	for(int i = 0; i < rows * cols; ++i){
		queue_visited[i] = 0;
	}

    ConstructQueue queue;
    memset(&queue,0,sizeof(queue));
    queue.front = 1;
    queue.rear = 0;
	queue_insert(&queue,start);
	ElementType a = 0;
	int passhead = 0;
	printf("route: \n");
	printf("start: %d ", start);
	while(queue_is_empty(&queue) == 0){
		int t = queue_pop(&queue, &a);
		queue_visited[t] = 1;
		queue_delete(&queue, &a);
		Node *tmp = &(m->list[t]);
		if(passhead != 0){
			printf("--> %d ", tmp->value);
		}
		++passhead;
        while(tmp){
			if(tmp->next && queue_visited[tmp->next->value] == 0){
				queue_insert(&queue, tmp->next->value);
				tmp = tmp->next;
			}
			tmp = tmp->next;
		}
	}
	printf("end\n");
	printf("\n");

	











	


    /*入队6个数据，最后两个入队失败*/
    // queue_insert(&queue,5);
    // queue_insert(&queue,4);
    // queue_insert(&queue,3);
    // queue_insert(&queue,2);
    // queue_insert(&queue,1);
    // queue_insert(&queue,0);

    // /*出队6个数据，最后两个出队失败*/
    // ElementType a = 0;
    // queue_delete(&queue,&a);
	// int res = queue_pop(&queue, &a);
	// printf("%d", res);
    // queue_delete(&queue,&a);
    // queue_delete(&queue,&a);
    // queue_delete(&queue,&a);
    // queue_delete(&queue,&a);
    // queue_delete(&queue,&a);

	
    return 0;
}