#include "kmeans.h"
#include <errno.h>
#define READ_ERROR_STRING "Error:\tFile was not in correct format.\n"
#define USAGE_STRING "USAGE:./executableName input_file k_value"


//  kmeans main function:
/* 
    INPUT:
        d * (n+1) 数组，记录
        k * n 数组，显示 k 个 centroid
    OUTPUT: 
        d * (n+1) 数组

    1. read in set of x's, y's and number of centroid
    2. calculate all points' distance with all centroids
        e.g. 10 points and 3 centroids, should calculate 30 distances 
    3. choose points that "belong" to each cluster
    4. update cluster centriod (average of points assigned to that cluster)
    5. calculate root mean square
    6. calculate the movement of centriods between this time's location and previous location
    7. repeate 2 - 6, till difference within threshold (centriods do not move anymore) and reach max iter number
*/

// read in data and return a 2D array
double ** read_data(const char * file_name, int * data_num, int * dimension_num){
    // This section will safely parse the value of k passed in to the program. If the argument cannot be parsed 
    // to an integer, or if it is larger than INT_MAX, we error out.
    if (file_name == NULL) {
        printf("Invalid file name or path");
        return NULL;
    }

    FILE *infile = fopen(file_name,"r");
    if(infile == NULL) {
        fprintf(stderr, "Could not open the file:\t%s\n", file_name);
        perror("Failed to open file");
        return NULL;
    }

    // This will read in the number of rows and columns (first line of the file). If it reads fewer than two 
    // things, we know the file is incorrect.
    int readIn = fscanf(infile, " %d %d", dimension_num, data_num); 

    if(readIn != 2) {
        fprintf(stderr, READ_ERROR_STRING);
        fclose(infile);
        return NULL;
    }

    // Makes a stack array with nRows rows and nCols columns.
    // May be indexed with data_array[i][j].
    double ** data_array = matrix_allocate(*data_num, *dimension_num);

    // This loop reads in the expected number of rows and columns. If it fails to read the expected number, 
    // it errors out. This doesn't catch some errors, E.G. too *many* lines in the input file, but you should 
    // not be editing those files for the assignment anyway.
    for (int i = 0; i < *dimension_num; ++i) {
        for (int j = 0; j < *data_num; ++j) {
            readIn = fscanf(infile," %lf", &(data_array[i][j]));
            // printf("%f\n", (data_array[i][j])); //TODO: comment out
            if(!readIn) {
                fprintf(stderr, READ_ERROR_STRING );
                return NULL;
            }
        }
    }

    // Since we've read in all the data we need, close the file.
    fclose(infile);
    printf("successfully import data");
    return data_array;
}


// allocate memory space for matrix: ## TODO: add allocate which matrix and which col in printf
double** matrix_allocate(int num_row, int num_col) {
    // check input row and col size
    if (num_row <= 0 || num_col <= 0) {
        printf("Invalid data size for creating matrix");
        return NULL;
    }

    // allocate memory:
    double **matrix = (double **) malloc(num_row * sizeof(double*));
    if(matrix == NULL) {
        printf("Memory allocation failed");
    }

    for (int i = 0; 1 < num_row; ++i) {
        matrix[i] = (double *) malloc (num_col * sizeof(double));
        if (matrix[i] == NULL) {
            printf("Memory allocation failed");
        }
    }

    return matrix;
}

// // free the matrix allocated by calling matrix_allocate function after we do not need the matrix any more
// int matrix_freeup(int num_row, int num_col, double **matrix) {
//     if (num_row <= 0 || num_col <= 0 || matrix == NULL) {
//         printf("Invalid data size for creating matrix");
//         return -1;
//     }

//     for (int i = 0; i < num_row; ++i){
//         free(matrix[i]);
//         matrix[i] = NULL;
//     }
//     free (matrix);
//     matrix = NULL;

//     return 1;
// }

// // initialized centriods
// void initialize_centroids(int cluster_num, int data_num, int dimension_num, double data_matrix[dimension_num][data_num], double ** centroid_matrix){
//     printf("-------------- initialize centroids -------------");
//     if (data_matrix == NULL || data_num <= 0 || dimension_num <= 0) {
//         printf("Error, cannot initialized centroid matrix");
//         return;
//     }

//     if (cluster_num <= 0 || cluster_num >= data_num) {
//         printf("Error, cannot initialized centroid matrix");
//         return;
//     }

//     for (int i = 0; i < cluster_num; ++cluster_num){
//         for (int j = 0; j < dimension_num; ++j) {
//             centroid_matrix[i][j] = data_matrix[i][j];
//             printf("%f", centroid_matrix[i][j]);
//         }
//     }

//     return;
// }

// data normalization 

// calc_distance func, return single distance

// calc_all_distance func

// calc_cluster_centroid

