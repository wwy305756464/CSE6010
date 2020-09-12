#ifndef kmeans_h
#define kmeans_h

#include<stdio.h>
#include<sys/malloc.h>
#include<stdlib.h>

double** read_data(const char * file_name, int * data_num, int * dimension_num);
double** matrix_allocate(int num_row, int num_col);
// int matrix_freeup(int num_row, int num_col, double **matrix);
// void initialize_centroids(int cluster_num, int data_num, int dimension_num, double data_matrix[dimension_num][data_num], double ** centroid_matrix);


#endif