#ifndef kmeans_h
#define kmeans_h

#include<stdio.h>
#include<sys/malloc.h>
#include<stdlib.h>

// print command when compile
void print_command(const char *program);

// allocate memory when creating vectors
int* vector_allocate(int vector_num);
double* vector_allocate_2(int vector_num);

// free up vector's memory
void vector_free(int vector_size, int *vector);

// allocate memory when creating matrix
double** matrix_allocate(int row_num, int col_num);

// free up matrix's memory
void matrix_free(double **matrix, int row_num, int col_num);

// read in data from file
double** read_data(const char *file_path, int *data_size, int *feature_size);

// normalized data
double ** normalize_data(double ** data_matrix, int data_num, int dimension_num);

// initialize centroid matrix
double ** initialize_centriods(double ** data_matrix, int cluster_num, int data_num, int dimension_num);

// randomly initialize centroid matrix
double ** initialize_centriods_random(double ** data_matrix, int cluster_num, int data_num, int dimension_num);

// calculate distance between two data points
double calculate_distance(double* data1, double* data2, int dimension_num);

// get distance matrix
double ** get_distance_matrix(double **data_matrix, double **centroid_matrix, int cluster_num, int data_num, int dimension_num);

// get cluster vector
int * get_cluster_vector(double ** distance_matrix, int cluster_num, int data_num);

// get how many points are in each cluster
int * get_cluster_points_number(double** data_matrix, int * cluster_vector, int cluster_num, int data_num);

// calculate root mean square
double root_mean_square(double** distance_matrix, int* cluster_vector, int cluster_num, int data_num);

// uodate centroids based on distance 
void update_centroids(double** data_matrix, double** centroid_matrix, int* cluster_vector, int* cluster_point_vector, int cluster_num, int data_num, int dimension_num);

// void initializeCentroids(int k, int data_size, int feature_size, double **data_matrix, double **centroids);



#endif