#include "search.h"

// readin doc file and n, output: O_location, X_location
char** read_origin_data(const char *file_name,  int *matrix_size){
	// printf("test reading in data \n");

	if(file_name == NULL) {
		printf("ERROR: Invalid file name or path\n");
		return NULL;
	}

    // This section will safely parse the value of k passed in to the program. If the argument cannot be parsed 
    // to an integer, or if it is larger than INT_MAX, we error out.
	FILE *data_file;
	data_file = fopen(file_name, "r");
	if(data_file == NULL) {
		printf("ERROR: Cannot open file for reading in data\n");
		return NULL;
	}

	// read the meta data regarding the data size and dimension information
	if(fscanf(data_file, "%d", matrix_size) != 1) {
		printf("ERROR: Data in the file not written in valid format! \n");
		return NULL;
	}

	// allocate the matrix variable to store data
	char **data_matrix = matrix_allocate_char(*matrix_size, *matrix_size);

	// read the data
	for(int i = 0; i < *matrix_size; i++) {
		// read the data of the ith row
		for(int j = 0; j < *matrix_size; j++) {
			// read the data of the jth feature of the ith data item
			if(fscanf(data_file, " %c", &data_matrix[i][j]) != 1) {
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


// generate a n * 2 matrix, to store location of each O or X
int** position_OX_func(char** data_matrix, char character, int *size, int *count){
    int** position_matrix = matrix_allocate_int(*size, 2); // 创建一个 n*2 的matrix用来存 O/X 的坐标位置
    int cnt = 0;
    for(int i = 0; i < *size; ++i){
        for(int j = 0; j < *size; ++j){
            if (data_matrix[i][j] == character){
                position_matrix[cnt][0] = i;
                position_matrix[cnt][1] = j;
                cnt++;
                //printf("%d, i: %d, j: %d \n", count, i, j);
            }
        }
    }
    *count = cnt;
    // printf("x: %d, y: %d \n", position_matrix[1][0], position_matrix[1][1]);
    return position_matrix;
}
// modify_domain_matrix(domain_matrix, position_X, matrix_size);
void modify_domain_matrix(int*** domain_matrix, int** position_matrix, int matrix_size, int count, char character){
    for (int i = 0; i < count; ++i){
        int pos_r = position_matrix[i][0];
        int pos_c = position_matrix[i][1];
        if (character == 'X'){
            domain_matrix[pos_r][pos_c][0] = 0;
        }
        else{
            domain_matrix[pos_r][pos_c][1] = 0;
        }
    }
}

// bool check_constraint_1(char** data_matrix, int num){

// }



/*
    allocate memory for int vector
    INPUT: vector's length
    OUTPUT: vector
*/
int* vector_allocate(int vector_num) {
	if(vector_num <= 0) {
		printf("ERROR: cannot allocate memory for vector\n");
		return NULL;
	}

	int *vector = (int*) malloc(vector_num * sizeof(int*));
	if(vector == NULL) {
		printf("ERROR: Memory allocation for vector failed\n");
		return NULL;
	}

	return vector;
}

/*
    allocate memory for matrix
    INPUT: matrix's size (rownum and colnum)
    OUTPUT: matrix
*/
char** matrix_allocate_char(int row_num, int col_num) {
    char ** matrix = NULL;
	if(row_num <= 0 || col_num <= 0) {
		printf("ERROR: Invalid input size when creating matrix\n");
		return NULL;
	}

	matrix = (char **) malloc(row_num * sizeof(char*));
	if(matrix == NULL) {
		printf("ERROR: Memory allocation failed\n");
	}

	for(int i = 0; i < row_num; i++) {
		matrix[i] = (char*) malloc(col_num * sizeof(char));
		if(matrix[i] == NULL) {
			printf("ERROR: Memory allocation for matrix failed\n");
			return NULL;
		}
	}

	return matrix;
}

int** matrix_allocate_int(int row_num, int col_num) {
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
		matrix[i] = (int*) malloc(col_num * sizeof(int));
		if(matrix[i] == NULL) {
			printf("ERROR: Memory allocation for matrix failed\n");
			return NULL;
		}
	}

	return matrix;
}


int*** matrix_allocate_3D(int row_num, int col_num) {
    int *** matrix = NULL;
    int thick_num = 2;
	if(row_num <= 0 || col_num <= 0) {
		printf("ERROR: Invalid input size when creating matrix\n");
		return NULL;
	}

    matrix = (int***) malloc(row_num * sizeof(int**));
    if(matrix == NULL){
        printf("ERROR: Memort allocation failed\n");
    }

    for(int i = 0; i < row_num; ++i){
        matrix[i] = (int**)malloc(col_num * sizeof(int*));
		if(matrix[i] == NULL) {
			printf("ERROR: Memory allocation for matrix failed\n");
			return NULL;
		}

        for(int j = 0; j < col_num; ++j){
            matrix[i][j] = (int*)malloc(thick_num * sizeof(int));
            if(matrix[i][j] == NULL) {
                printf("ERROR: Memory allocation for matrix failed\n");
                return NULL;
		}
        }
    }
    // int value = 1;
    // for (int a = 0; a < row_num; ++a){
    //     for (int b = 0; b < col_num; ++b){
    //         for (int c = 0; c < thick_num; ++c){
    //             *(*(*(matrix+a)+b)+c) = value++;
    //         }
    //     }
    // }
	return matrix;
}






// TODO: constraint 1

// TODO: constraint 2

// TODO: constraint 3