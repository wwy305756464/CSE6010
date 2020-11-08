#include "maze.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <limits.h>


int main(int argc, char * argv[]){
    if(argc != 4){
        printf("Please enter correct arguments \n");
        return 1;
    }

    
    char *endptr = NULL;
    int base = 10;
    errno = 0;
    long int long_row = strtol(argv[1], &endptr, base);
    long int long_col = strtol(argv[2], &endptr, base);

    // This will trigger if an error was encountered when trying to parse the input, or if the input was not a 
    // proper integer (e.g. 124A). This can also trigger if the input is too long to fit even in a long int.
    if((errno != 0) || (*endptr != '\0')) {
        fprintf(stderr, "The input: \"%s\" could not be parsed as an integer.\""
        " \n", argv[2]);
        return 1;
    }
        

    int rownum = (int) long_row;	
    int colnum = (int) long_col;	

    const char *file_name = argv[3];

    int vs[colnum * rownum];
    int visited[colnum * rownum];
    int parents[colnum * rownum];
    for(int i = 0; i < colnum * rownum; ++i){
        vs[i] = i;
    }
    for(int i = 0; i < colnum * rownum; ++i){
        visited[i] = 0;
    }
    MLL m = initial_maze(vs, colnum * rownum);
    time_t t;
    srand((unsigned) time(&t));
    int start_point = rand() % (colnum * rownum);
    // printf("start point: ")
    int end_point;
    printf("The value is %d \n", start_point);
    int pre_node = start_point;
    int tcnt = 1;
    int longpath = 0, tlongpath = -100;
    while(tcnt < colnum * rownum){
        longpath = 0;
        visited[pre_node] = 1;
        int left = -1;
        int right = 1;
        int up = -colnum;
        int down = colnum;
        //int randomseed = rand() % 4;
        //int Dire[4] = {left, right, up, down};
        //int next_node = pre_node + Dire[randomseed];
        int next_node = -1;
        int randomseed = 0;
        int wcnt = 0;
        int tag = 0;
        int flag = 1;
        while(flag == 1){
            randomseed = rand() % 4;
            int Dire[4] = {left, right, up, down};
            next_node = pre_node + Dire[randomseed];
            //end_point = next_node;
            ++wcnt;
            if((visited[next_node] == 1 || next_node < 0 || next_node >= colnum * rownum || (randomseed == 0 && next_node % colnum == (colnum - 1)) || (randomseed == 1 && next_node % colnum == 0)) && (wcnt < 50)){
                continue;
            }else{
                if(wcnt < 50){
                    parents[next_node] = pre_node;
                    flag = 0;
                }else{
                    pre_node = parents[pre_node];
                    tag = 1;
                    flag = 0;
                }
            }
        }
        if(tag == 1){
            continue;
        }else{
            ++longpath;
            visited[next_node] = 1;
            ++tcnt;
            add_edge(pre_node, next_node, m);
            pre_node = next_node;
            if(longpath > tlongpath){
                tlongpath = longpath;
                end_point = next_node;
            }
        }
    }

    print_maze(m);
    int** temp_matrix = matrix_allocate(colnum*rownum, colnum*rownum);
    for (int i = 0; i < colnum*rownum; ++i){
        for (int j = 0; j < colnum*rownum; ++j){
            temp_matrix[i][j] = -1;
        }
    }

    int n = m->vertex;
    for(int j = 0; j < n; ++j){
        Node *tmp = &(m->list[j]);
        int k = 0;
        while(tmp){
            if(tmp->next){
            temp_matrix[j][k] = tmp->next->value;
            // printf("%d ", tmp->value);
            }
            tmp = tmp->next;
            k++;
        }    
    }

    for(int i = 0; i < colnum*rownum; ++i){
        int t = 0;
        int flag = 0;
        while(temp_matrix[i][t] != -1){
            ++t;
        }
        for(int j = 0; j < n; ++j){
            int y = 0;
            while(temp_matrix[j][y] != -1){
                if(temp_matrix[j][y] == i){
                    for(int p = 0; p < t; ++p){
                        if(temp_matrix[i][p] == j){
                            flag = 1;
                        }
                    }
                    if(flag == 0){
                        temp_matrix[i][t++] = j;
                    }
                    flag = 0;
                }
                ++y;
            }
        }
    }

    FILE *fpWrite=fopen(file_name,"w");  
    if(fpWrite==NULL)  
    {  
        return 0;  
    }  
    fprintf(fpWrite, "%d %d \n", rownum, colnum);
    fprintf(fpWrite, "%d %d \n", start_point, end_point);
    // int n = m->vertex;
    for(int i = 0; i < rownum*colnum; ++i){
        for (int j = 0; j < rownum * colnum; ++j){
            if (temp_matrix[i][j] != -1){
                fprintf(fpWrite, "%d ", temp_matrix[i][j]);
            }
            
        }
        fprintf(fpWrite, "\n");
    }
    fclose(fpWrite);  

    return 0;
}