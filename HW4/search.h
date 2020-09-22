#ifndef search_h
#define search_h

#include<stdio.h>
#include<sys/malloc.h>
#include<stdlib.h>

char** read_origin_data(const char *file_name,  int *matrix_size);
int* vector_allocate(int vector_num);
char** matrix_allocate_char(int row_num, int col_num);
int** matrix_allocate_int(int row_num, int col_num);
int*** matrix_allocate_3D(int row_num, int col_num);
int** position_OX_func(char** data_matrix, char character, int *size, int *count); // 可能要加*
void modify_domain_matrix(int*** domain_matrix, int** position_matrix, int matrix_size, int count, char character);

#endif