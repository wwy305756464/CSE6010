#ifndef search_h
#define search_h

#include<stdio.h>
#include<sys/malloc.h>
#include<stdlib.h>
#include<stdbool.h>

char** read_origin_data(const char *file_name,  int *matrix_size);
int* vector_allocate(int vector_num);
char** matrix_allocate_char(int row_num, int col_num);
int** matrix_allocate_int(int row_num, int col_num);
int*** matrix_allocate_3D(int row_num, int col_num);
int** position_OX_func(char** data_matrix, char character, int *size, int *count); // 可能要加*
void modify_domain_matrix(int*** domain_matrix, int** position_matrix, int matrix_size, int count, char character);

// constraint test
bool check_constraint_1(int* vector, int matrix_size);
bool check_constraint_2(int* vector, int matrix_size, int cur_index);
bool check_constraint_3_row(int** puzzle_matrix, int r_num, int c_num, int matrix_size);
bool check_constraint_3_col(int** puzzle_matrix, int r_num, int c_num, int matrix_size);
bool compare_array(int* array1, int* array2, int n);

// final check of generated matrix
bool final_check_constraint_1(char** puzzle_matrix, int matrix_size);
bool final_check_constraint_2(char** puzzle_matrix, int matrix_size);
bool final_check_constraint_3(char** puzzle_matrix, int matrix_size);

// 
char** substitude_to_OX(int** puzzle_matrix, int matrix_size);
void print_puzzle_result(char** puzzle_matrix, int matrix_size);
void vector_free(int *vector, int vector_num);
void matrix_free_int(int **matrix, int row_num, int col_num);
void matrix_free_char(char **matrix, int row_num, int col_num);
void matrix_free_3D(int*** matrix, int row_num, int col_num); 
#endif