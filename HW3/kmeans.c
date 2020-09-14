#include "kmeans.h"
#include <time.h>
#include <math.h>

/* 
    print commands when compiling the program
    INPUT: program name
    OUTPUT: none
*/
void print_command(const char *program) {
    printf("please type these parameters when compiling: %s input_data cluster_num \n", program);
    printf("where:\n");
    printf("input_data -> input dataset file\n");
	printf("cluster_num -> number of clusters\n");
    printf("\nExample: %s WineData_2col.txt 3\n", program);
}

/*
    allocate memory for matrix
    INPUT: matrix's size (rownum and colnum)
    OUTPUT: matrix
*/
double** matrix_allocate(int row_num, int col_num) {
    printf(" -> test matrix allocation \n");
	// check for input values
    double ** matrix = NULL;
	if(row_num <= 0 || col_num <= 0) {
		printf("Invalid input size when creating matrix");
		return NULL;
	}

	// allocate memory
	matrix = (double **) malloc(row_num * sizeof(double*));
	if(matrix == NULL) {
		printf("Memory allocation failed");
	}

	for(int i = 0; i < row_num; i++) {
		matrix[i] = (double *) malloc(col_num * sizeof(double));
		if(matrix[i] == NULL) {
			printf("Memory allocation for matrix failed");
			return NULL;
		}
	}

	return matrix;
}


int* vector_allocate(int vector_num) {
	if(vector_num < 0) {
		printf("cannot allocate memory for vector");
		return NULL;
	}

	// allocate the memory space for cluster label storing
	int *vector = (int*) malloc(vector_num * sizeof(int*));

	// check the return value of malloc()
	if(vector == NULL) {
		printf("Memory allocation for vector failed");
		return NULL;
	}

	return vector;
}

double* vector_allocate_2(int vector_num) {
	if(vector_num < 0) {
		printf("cannot allocate memory for vector");
		return NULL;
	}

	// allocate the memory space for cluster label storing
	double *vector = (double*) malloc(vector_num * sizeof(double*));

	// check the return value of malloc()
	if(vector == NULL) {
		printf("Memory allocation for vector failed");
		return NULL;
	}

	return vector;
}


/*
    free up matrix memory, will be called when matrix will not use any more
    INPUT: matrix, matrix's size (row num and col num)
    OUTPUT: none
*/
void matrix_free(double **matrix, int row_num, int col_num) { //FIXME: 改comment
    printf(" -> test matrix free \n");
	// check for invalid inputs
	if(row_num <= 0 || col_num <= 0) {
		printf("Invalid matrix dimension values!");
		return;
	}
	if(matrix == NULL) {
		printf("No matrix to free!");
		return;
	}

	// begin to free our input matrix
	for(int i = 0; i < row_num; i++) {
		free(matrix[i]);
		matrix[i] = NULL;
	}
	free(matrix);
	matrix = NULL;

	return;
}


void vector_free(int vector_num, int *vector) { // FIXME: 改comment
	// check for invalid inputs
	if(vector_num < 0) {
		printf("Invalid vector size!");
		return;
	}
	if(vector == NULL) {
		printf("No vector to free!");
		return;
	}

	// free the vector
	free(vector);
	vector = NULL;

	return;
}

/*
    read in data from given txt file and store as matrix
    INPUT: input file name, number of datas, number of dimensions or features
    OUTPUT: generated data matrix
*/
double** read_data(const char *file_name, int *data_num, int *dimension_num) {
	printf("test reading in data \n");

	if(file_name == NULL) {
		printf("Invalid file name or path");
		return NULL;
	}

    // This section will safely parse the value of k passed in to the program. If the argument cannot be parsed 
    // to an integer, or if it is larger than INT_MAX, we error out.
	FILE *data_file;
	data_file = fopen(file_name, "r");
	if(data_file == NULL) {
		printf("Cannot open file for reading in data");
		return NULL;
	}

	// read the meta data regarding the data size and dimension information
	if(fscanf(data_file, "%d %d", data_num, dimension_num) != 2) {
		printf("ERROR: Data in the file not written in valid format!");
		return NULL;
	}

	// allocate the matrix variable to store data
	double **data_matrix = matrix_allocate(*data_num, *dimension_num);

	// read the data
	for(int i = 0; i < *data_num; i++) {
		// read the data of the ith row
		for(int j = 0; j < *dimension_num; j++) {
			// read the data of the jth feature of the ith data item
			if(fscanf(data_file, " %lf", &data_matrix[i][j]) != 1) {
				printf("ERROR: the data in row %d and column %d failed to get read", i, j);
				return NULL;
			}
		}
	}

	// printf("%f", data_matrix[1][1]);
	// close the file
	fclose(data_file);
	return data_matrix;
}


double ** normalize_data(double ** data_matrix, int data_num, int dimension_num){ //FIXME: 
	if (data_matrix == NULL || data_num < 0 || dimension_num < 0){
		printf("cannot normalize data");
		return NULL;
	}

	double* average_vector = vector_allocate_2(dimension_num);
	for (int i = 0; i < dimension_num; ++i){
		double sum = 0;
		for (int j = 0; j < data_num; ++j){
			sum += data_matrix[j][i];
		}
		average_vector[i] = sum / data_num;
	}

	double** normalized_data_matrix = matrix_allocate(data_num, dimension_num);
	for (int i = 0; i < dimension_num; ++i){
		for (int j = 0; j < data_num; ++j){
			double sigma = sqrt( (data_matrix[j][i] - average_vector[i]) * (data_matrix[j][i] - average_vector[i]) / data_num);
			normalized_data_matrix[j][i] = (data_matrix[j][i] - average_vector[i]) / sigma;
		}
	}

	return normalized_data_matrix;
	
}

/*
    initialize first cluster_num data points as initial centroids
    INPUT: number of clusters, number of dimensions, original data matrix, and initialized centroid matrix
*/
double ** initialize_centriods(double ** data_matrix, int cluster_num, int data_num, int dimension_num) {
    if (data_matrix == NULL || cluster_num <= 0 || dimension_num <= 0 || data_num <= 0 || cluster_num > data_num) {
        printf("cannot initialize centroids");
        return NULL;
    }
    
    double **centroid_matrix = matrix_allocate(cluster_num, dimension_num);

    for (int i = 0; i < cluster_num; ++i) {
        for (int j = 0; j < dimension_num; ++j) {
            centroid_matrix[i][j] = data_matrix[i][j];
        }
    }

    return centroid_matrix;
}

double ** initialize_centriods_random(double ** data_matrix, int cluster_num, int data_num, int dimension_num) { //FIXME:
    if (data_matrix == NULL || cluster_num <= 0 || dimension_num <= 0 || data_num <= 0 || cluster_num > data_num) {
        printf("cannot initialize centroids");
        return NULL;
    }
    
    double **centroid_matrix_random = matrix_allocate(cluster_num, dimension_num);

	srand((unsigned)time(NULL));
	for (int i = 0; i < cluster_num; ++i) {
		int rand_index = rand() % data_num;
		printf("random: %d", rand_index);
		for (int j = 0; j < dimension_num; ++j) {
			centroid_matrix_random[i][j] = data_matrix[rand_index][j];
		}
	}
	
    // for (int i = 0; i < cluster_num; ++i) {
    //     for (int j = 0; j < dimension_num; ++j) {
    //         centroid_matrix_random[i][j] = data_matrix[i][j];
    //     }
    // }

    return centroid_matrix_random;
}


double calculate_distance(double* data1, double* data2, int dimension_num){
	if (data1 == NULL || data2 == NULL || dimension_num < 0) {
		printf("cannot calulate distance between two points");
		return -1;
	}

	double distance = 0.0;
	for (int i = 0; i < dimension_num; ++i){
		distance += (data1[i] - data2[i]) * (data1[i] - data2[i]);
	}

	distance = sqrt(distance);
	return distance;
}


double ** get_distance_matrix(double **data_matrix, double **centroid_matrix, int cluster_num, int data_num, int dimension_num){
	if (data_matrix == NULL || centroid_matrix == NULL || cluster_num < 0 || data_num < 0 || dimension_num == 0 || cluster_num > data_num){
		printf("cannot get distance matrix");
		return NULL;
	}

	double ** distance_matrix = matrix_allocate(data_num, cluster_num);
	for (int i = 0; i < data_num; ++i){
		for (int j = 0; j < cluster_num; ++j){
			distance_matrix[i][j] = calculate_distance(data_matrix[i], centroid_matrix[j], dimension_num);
		}
	}

	return distance_matrix;
}


int * get_cluster_vector(double ** distance_matrix, int cluster_num, int data_num){
	if (data_num < 0 || cluster_num < 0 || distance_matrix == NULL ){
		printf("cannot create cluster vector");
		return NULL;
	}

	int closest_cluster_index;
	int* cluster_vector = vector_allocate(data_num);
	for (int i = 0; i < data_num; ++i){
		closest_cluster_index = 1;
		for (int j = 0; j < cluster_num; ++j){
			int temp = distance_matrix[i][closest_cluster_index - 1];
			if (distance_matrix[i][j] < temp){
				closest_cluster_index = j + 1;
			}
		}
		cluster_vector[i] = closest_cluster_index;
		// printf("cluster: %d", cluster_vector[1]);
	}

	return cluster_vector;
}


int * get_cluster_points_number(double** data_matrix, int * cluster_vector, int cluster_num, int data_num){
	if (data_matrix == NULL || cluster_vector == NULL || cluster_num < 0 || data_num < 0 || cluster_num > data_num){
		printf("cannot get how many points in each cluster");
		return NULL;
	}

	int* cluster_point_vector = vector_allocate(cluster_num);
	for (int i = 0; i < cluster_num; ++i){
		cluster_point_vector[i] = 0;
	}

	for (int i = 0; i < data_num; ++i) {
		int place = cluster_vector[i] - 1;
		cluster_point_vector[place]++;
	}

	for (int i = 0; i < cluster_num; ++i){
		printf("cluster:");
		printf("%d\n",cluster_point_vector[i]);
	}

	return cluster_point_vector;
}

double root_mean_square(double** distance_matrix, int* cluster_vector, int cluster_num, int data_num){
	if (distance_matrix == NULL || cluster_vector == NULL || cluster_num < 0 || data_num < 0 || cluster_num > data_num){
		printf("cannot calculate root mean square");
		return 0;
	}

	double root_mean_square = 0.0;
	for (int i = 0; i < data_num; ++i) {
		double s = distance_matrix[i][cluster_vector[i] - 1] * distance_matrix[i][cluster_vector[i] - 1];
		root_mean_square += s;
	}

	printf("RMS: %.2f \n", root_mean_square);
	return root_mean_square;
}

void update_centroids(double** data_matrix, double** centroid_matrix, int* cluster_vector, int* cluster_point_vector, int cluster_num, int data_num, int dimension_num){
	if(data_matrix == NULL || centroid_matrix == NULL || cluster_vector == NULL || cluster_point_vector == NULL || cluster_num < 0 || data_num < 0 || dimension_num < 0 || cluster_num > data_num){
		printf("cannot update centroids");
		return;
	}

	for (int i = 0; i < cluster_num; ++i){
		for (int j = 0;  j < dimension_num; ++j){
			centroid_matrix[i][j] = 0.0;
		}
	}

	for(int i = 0; i < data_num; ++i){
		for (int j = 0; j < dimension_num; ++j){
			int num = cluster_vector[i] - 1;
			centroid_matrix[num][j] += data_matrix[i][j];
		}
	}

	for (int i = 0; i < cluster_num; ++i){
		for (int j = 0; j < dimension_num; ++j){
			int points_num = cluster_point_vector[i];
			centroid_matrix[i][j] = centroid_matrix[i][j] / points_num;
		}
	}

	return;
}

