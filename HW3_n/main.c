/*
 * main.c
 *
 *  Created on: Sep 19, 2017
 *      Author: kunzheng
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function Prototypes for usage function
void usage(const char *programName);

// Function Prototypes
int*         allocateVector(int vector_size);
double**     allocateMatrix(int row_num, int col_num);
double**     readData(const char *file_path, int *data_size, int *feature_size);
void         writeFormatedInput(int data_size, int feature_size, double **data_matrix);
void         initializeCentroids(int k, int data_size, int feature_size, double **data_matrix, double **centroids);
int          freeVector(int vector_size, int *vector);
int          freeMatrix(int row_num, int col_num, double **matrix);

// Main Function
int main(int argc, char * argv[]) {
	// Start by reading the input from the command line prompt
	// In this k-means implementation, the program takes in 5 addition arguments:
	    //(1) number of cluster;
		//(2) maximum number of iteration time;
		//(3) minimum improvement rate used as a threshold to stop k-means;
		//(4) path of data file;
		//(5) path of result file;

		if (argc != 6) {
	        usage(argv[0]);
	        return 1;
	    }
	    int k = (int) strtol(argv[1], NULL, 10);          // number of clusters
	    int n_iter = (int) strtol(argv[2], NULL, 10);     // maximum number of iterations
	    double min_improve = strtod(argv[3], NULL);       // improvement threshold to stop k-means
	    const char *data_path = argv[4];                        // file path to load data file
	    const char *output_file = argv[5];                       // file path of result data file

	    // This part of main function uses the above parameters to run our k-means

	    // initialization
	    int data_size = 0;
	    int feature_size = 0;
	    double **data_matrix = readData(data_path, &data_size, &feature_size);
	    double **centroids = allocateMatrix(k, feature_size);
	    int iter = 0;
	    double improvement = -1;

	    initializeCentroids(k, data_size, feature_size, data_matrix, centroids);
	    // write formatted input data to separate file for further test of the correctness of our k-means
	    // writeFormatedInput(data_size, feature_size, data_matrix);

	    // begin training the data
	    while(iter < n_iter) {
	    		printf("Begin the %dth iteration...\n", iter);
	    		if(improvement <= min_improve) break;
	    		iter++;
	    }


	    // write the result data used for knn to the output file
	    // writeClusterResults(data_size, feature_size, output_file, data_matrix, cluster_label);

	    // set all the spaces free
	    freeMatrix(data_size, feature_size, data_matrix);


	    return 1;
}

// usage function reused from the first assignment, originally written by Karl Gemayel
/**
 * Print out the usage message.
 *
 * @param programName the name of the executable file.
 */
void usage(const char *programName) {
    printf("usage: %s  k n_iter min_improve data_file output_file\n", programName);
    printf("where:\n");
    printf("    k           : number of clusters\n");
    printf("    n_iter      : maximum number of iterations if the minimum threshold on improvement cannot be reached\n");
    printf("    min_improve : threshold of improvement on objective function to stop k-means\n");
    printf("    data_path   : where in the disk to load your data used for training k-means\n");
    printf("    output_file : where in the disk to store results of k-means\n");
    printf("\nExample: %s 10 100 0.01 gbm-KM.norm gbm-KM-results.csv\n", programName);
}

// Function Implementations


/*
 *The function used to allocate memory space when we need to dynamically declare a 1-d
 *array to store values
 *@param vector_size: size of data to be stored in the allocated 1-d array
 *@return: an int value indicating whether function execution is successful or not
 */
int* allocateVector(int vector_size) {
	// check for invalid inputs
	if(vector_size < 0) {
		printf("Invalid vector size");
		return NULL;
	}

	// allocate the memory space for cluster label storing
	int *vector = (int*) malloc(vector_size * sizeof(int*));

	// check the return value of malloc()
	if(vector == NULL) {
		printf("Memory space allocation unsuccessful!");
		return NULL;
	}

	return vector;
}

/*
 * This function is frequently used in our k-means implementation. Before data can be written into some variable, we
 * need firstly allocate memory space for the variable. Our readData() and
 * allocateMatrix() require this be done during run time, where the function become useful.
 * @param row_num: the number of rows to generate
 * @param col_num: the number of columns to generate
 * @return: a pointer of pointer, namely a pointer to a 2-d array
 */
double** allocateMatrix(int row_num, int col_num) {
	// check for input values
	if(row_num <= 0) {
		printf("Invalid data size!");
		return NULL;
	}
	if(col_num <= 0) {
		printf("Invalid feature size!");
		return NULL;
	}

	// allocate memory for matrix rows and check the allocation
	double **matrix = (double **) malloc(row_num * sizeof(double*));
	if(matrix == NULL) {
		printf("Memory allocation for matrix rows failed!");
	}

	// allocate memory for matrix columns and check the allocation
	for(int i = 0; i < row_num; i++) {
		matrix[i] = (double *) malloc(col_num * sizeof(double));
		if(matrix[i] == NULL) {
			printf("Memory allocation for %dth column failed!", i);
		}
	}

	return matrix;
}

/*
 *This function used for free the vector allocated by allocateVector() after it becomes useless
 *@param vector_size: the size of data to stored in the vector
 *@param vector: vector to free, a pointer variable
 *@return: a int value indicating whether the execution is successful, if not return -1
 */
int freeVector(int vector_size, int *vector) {
	// check for invalid inputs
	if(vector_size <= 0) {
		printf("Invalid vector size!");
		return -1;
	}
	if(vector == NULL) {
		printf("No vector to free!");
		return -1;
	}

	// free the vector
	free(vector);
	vector = NULL;

	return 1;
}

/*
*This function used for free the matrix allocated by allocateMatrix() after it becomes useless
 *@param row_num: number of rows to allocate
 *@param col_num: number of columns to allocate
 *@return: an int value indicating whether the execution is successful, if not return -1
 */
int freeMatrix(int row_num, int col_num, double **matrix) {
	// check for invalid inputs
	if(row_num <= 0 || col_num <= 0) {
		printf("Invalid matrix dimension values!");
		return -1;
	}
	if(matrix == NULL) {
		printf("No matrix to free!");
		return -1;
	}

	// begin to free our input matrix
	for(int i = 0; i < row_num; i++) {
		free(matrix[i]);
		matrix[i] = NULL;
	}
	free(matrix);
	matrix = NULL;

	return 1;
}

/*
 * this function reads the raw training data from a file, and returns a 2-d array, with
 * each column corresponding to a feature of data and each row to a data point, namely a
 * cell.
 *
 * @param file_path: a string variable indicating where in the system the data file is stored
 * @data_matrix: a 2-d array pointer variable with all data stored: a row <-> a data; a column <-> a feature
 * @param data_size: a pointer used to pass the number of data when function get executed
 * @param feature_size: a pointer used to pass the number of features of data
 */
double** readData(const char *file_path, int *data_size, int *feature_size) {
	printf("start reading in data");
	// test for invalid inputs
	if(file_path == NULL) {
		// if the path is null
		printf("%s", "Please enter a valid path!");
		return NULL;
	}

	// create file reader variable and open the file
	FILE *data_file;
	data_file = fopen(file_path, "r");
	if(data_file == NULL) {
		// if the file does not exist
		printf("%s", "The file does not exist!");
		return NULL;
	}

	// read the meta data regarding the data size and dimension information
	if(fscanf(data_file, "%d %d", data_size, feature_size) != 2) {
		printf("ERROR: Data in the file not written in valid format!");
		return NULL;
	}

	// allocate the matrix variable to store data
	double **data_matrix = allocateMatrix(*data_size, *feature_size);

	// read the data
	for(int i = 0; i < *data_size; i++) {
		// read the data of the ith row
		for(int j = 0; j < *feature_size; j++) {
			// read the data of the jth feature of the ith data item
			if(fscanf(data_file, " %lf", &data_matrix[i][j]) != 1) {
				printf("ERROR: the data in row %d and column %d failed to get read", i, j);
				return NULL;
			}
		}
	}

	printf("%f", data_matrix[1][1]);
	// close the file
	fclose(data_file);

	return data_matrix;
}

/*
 *This function is used to set the k centroid to their initial values. In this assignment,
 *it is the first k rows in the data matrix
 *@param k: number of clusters
 *@param data_size: size of data to do clustering
 *@param feature_size: size of features used in k-means
 *@param data_matrix: a 2-d array with original data values stored
 *@param centroids: an 2-d array with memory space allocated for it to store centroid coordinate values
 */
void initializeCentroids(int k, int data_size, int feature_size, double **data_matrix, double **centroids) {
	// check for invalid inputs
	if(data_matrix == NULL) {
		printf("No data to be used for initialization!");
		return;
	}
	if(data_size <= 0) {
		printf("Invalid data size!");
		return;
	}
	if(feature_size <= 0) {
		printf("Invalid feature size!");
		return;
	}
	if(k <= 0 || k > data_size) {
		printf("Invalid k for k-means!");
		return;
	}

	// fill the centroids matrix with data by the first 5 rows in data_matrix
	for(int i = 0; i < k; i++) {
		for(int j = 0; j < feature_size; j++) {
			centroids[i][j] = data_matrix[i][j];
		}
	}

	return;
}

