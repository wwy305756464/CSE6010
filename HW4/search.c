#include "search.h"
#include <stdbool.h>


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


// generate a matrix, to store location of each O or X
int** position_OX_func(char** data_matrix, char character, int *size, int *count){
    int** position_matrix = matrix_allocate_int((*size)*(*size), 2); 
    int cnt = 0;
    int tmp = 0;
    for(int i = 0; i < *size; ++i){
        for(int j = 0; j < *size; ++j){
            if (data_matrix[i][j] == character){
                position_matrix[cnt][0] = i;
                position_matrix[cnt][1] = j;
                cnt++;
            }
        }
    }
    *count = cnt; //  use count 
    return position_matrix;
}


// modify_domain_matrix(domain_matrix, position_X, matrix_size);
void modify_domain_matrix(int*** domain_matrix, int** position_matrix, int matrix_size, int count, char character){
    for (int i = 0; i < count; ++i){
        int pos_r = position_matrix[i][0];
        int pos_c = position_matrix[i][1];
        if (character == 'X'){
            domain_matrix[pos_r][pos_c][1] = 1;
        }
        else{
            domain_matrix[pos_r][pos_c][0] = 100;
        }
    }
}


// check each row / col has same number of O and X
bool check_constraint_1(int* vector, int matrix_size){
    int sum = 0;
    for (int i = 0; i < matrix_size; ++i){
        sum += vector[i];
    }
    int num_of_X = sum % 100;
    int num_of_O = sum / 100;

    if (num_of_O <= matrix_size / 2 && num_of_X <= matrix_size / 2){
        return true;
    }

    if ((num_of_X == matrix_size / 2) && (num_of_O == matrix_size / 2)){
        return true;
    }
    else{
        return false;
    }
}


// check constraint 2:
bool check_constraint_2(int* vector, int matrix_size, int cur_index){
    if(vector[2] == 0){ // if number of elements < 3, return ture
        return true;
    }

    // check whether numbers are equal
    if((vector[cur_index] == vector[cur_index - 1]) && (vector[cur_index] == vector[cur_index - 2])) {
        return false;
    }

    return true;
}


bool check_constraint_3_row(int** puzzle_matrix, int r_num, int c_num, int matrix_size){
    if (c_num != 5) { // if not full filled, return true
        return true;
    }
    if (r_num == 0) { // if only first row, resturn true
        return true;
    }

    int* current_row = vector_allocate(matrix_size);
    int** previous_rows = matrix_allocate_int(r_num, matrix_size); 

    for(int r = 0; r <= r_num; ++r){  
        for(int c = 0; c < matrix_size; ++c){
            if (r == r_num){
                current_row[c] = puzzle_matrix[r][c];
            }
            else{
                previous_rows[r][c] = puzzle_matrix[r][c];
            }
        }
    } 
    // e.g. 
    // [ 100 1   1   100 100 1   ]  -->  row0
    // [ 100 1   100 1   1   100 ]  -->  row1
    // [ 1   100 1   1   100 100 ]  -->  row2
    // [ 100 1   1   100 100 1   ]  -->  row3


    bool check_res = true;
    bool check_temp = true;
    for(int i = 0; i < r_num; ++i){
        check_temp = compare_array(current_row, previous_rows[i], matrix_size);
        if(check_temp == true){
            check_res = false;
            break;
        }
    }

    vector_free(current_row, matrix_size);
    matrix_free_int(previous_rows, r_num, matrix_size);
    return check_res;
}


bool check_constraint_3_col(int** puzzle_matrix, int r_num, int c_num, int matrix_size){
    if (r_num != 5) {
        return true;
    }
    if (c_num == 0) { 
        return true;
    }

    int* current_col = vector_allocate(matrix_size);
    int** previous_cols = matrix_allocate_int(c_num, matrix_size);

    for(int c = 0; c <= c_num; ++c){  
        for(int r = 0; r < matrix_size; ++r){
            if (c == c_num){
                current_col[r] = puzzle_matrix[r][c];
            }
            else{
                previous_cols[c][r] = puzzle_matrix[r][c];
            }
        }
    } 

    bool check_res = true;
    bool check_temp = true;
    for(int i = 0; i < c_num; ++i){
        check_temp = compare_array(current_col, previous_cols[i], matrix_size);
        if(check_temp == true){
            check_res = false;
            break;
        }
    }

    vector_free(current_col, matrix_size);
    matrix_free_int(previous_cols, c_num, matrix_size);
    return check_res;
}


bool compare_array(int* array1, int* array2, int n){  // 两个array完全相等返回true
    for (int i = 0; i < n; ++i){
        if (array1[i] != array2[i]) return false;
    }
    return true;
}

// final test function, test with three constraints for whole final matrix, can write three functions
// check with generated matrix of constraint 1, each row and col has same number of O and X:
bool final_check_constraint_1(char** puzzle_matrix, int matrix_size){

    // check each row:
    int cntx = 0, cnto = 0;
    bool res = true;
    for(int r = 0; r < matrix_size; ++r){
        for(int c = 0; c < matrix_size; ++c){
            if(puzzle_matrix[r][c] == 'O'){
                ++cnto;
            }else{
                ++cntx;
            }
        }
        if(cnto != (matrix_size / 2) || cntx != (matrix_size / 2)){
            res = false;
        }
        cnto = 0, cntx = 0;
    }

    // check each col:
    for(int c = 0; c < matrix_size; ++c){
        for(int r = 0; r < matrix_size; ++r){
            if(puzzle_matrix[r][c] == 'O'){
                ++cnto;
            }else{
                ++cntx;
            }
        }
        if(cnto != (matrix_size / 2) || cntx != (matrix_size / 2)){
            res = false;
        }
        cnto = 0, cntx = 0;
    }

    return res;
}

//Check there is not a continues symbol
bool final_check_constraint_2(char** puzzle_matrix, int matrix_size){
    bool res = true;
    for(int r = 0; r < matrix_size; ++r){
        for(int c = 0; c < matrix_size - 2; ++c){
            if(puzzle_matrix[r][c] == puzzle_matrix[r][c+1] && puzzle_matrix[r][c+1] == puzzle_matrix[r][c+2]){
                res = false;
            }
        }
    }
    for(int c = 0; c < matrix_size; ++c){
        for(int r = 0; r < matrix_size - 2; ++r){
            if(puzzle_matrix[r][c] == puzzle_matrix[r+1][c] && puzzle_matrix[r+1][c] == puzzle_matrix[r+2][c]){
                res = false;
            }
        }
    }
    return res;
}

//Check eaach row and column is unique
bool final_check_constraint_3(char** puzzle_matrix, int matrix_size){
    bool res = true;
    int cnt = 0;
    for(int c = 0; c < matrix_size; ++c){
        for(int i = 0; i < matrix_size; ++i){
            for(int j = i + 1; j < matrix_size; ++j){
                if(puzzle_matrix[i][c] != puzzle_matrix[j][c]){
                    ++cnt;
                }
                if(cnt == matrix_size){
                    res = false;
                }
            }
            cnt = 0;
        }
    }
    cnt = 0;
    for(int r = 0; r < matrix_size; ++r){
        for(int i = 0; i < matrix_size; ++i){
            for(int j = i + 1; j < matrix_size; ++j){
                if(puzzle_matrix[r][i] != puzzle_matrix[r][j]){
                    ++cnt;
                }
                if(cnt == matrix_size){
                    res = false;
                }
            }
            cnt = 0;
        }
    }
    return res;
}


// print out final matrix
void print_puzzle_result(char** puzzle_matrix, int matrix_size){
    int cnt = 0;
    for (int i = 0; i < matrix_size; ++i){
        for(int j = 0; j < matrix_size; ++j){
            printf("%c\t", puzzle_matrix[i][j]);
            cnt++;
        }
        if (cnt % matrix_size == 0){
            printf("\n");
        }

    }
}

char** substitude_to_OX(int** puzzle_matrix, int matrix_size){
    char** OX_matrix = matrix_allocate_char(matrix_size, matrix_size);
    for (int i = 0; i < matrix_size; ++i){
        for (int j = 0; j < matrix_size; ++j){
            if (puzzle_matrix[i][j] == 1){
                OX_matrix[i][j] = 'X';
            }
            else {
                OX_matrix[i][j] = 'O';
            }
        }
    }
    return OX_matrix;
}


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
	return matrix;
}

// memory free functions
void vector_free(int *vector, int vector_num) { 
	if(vector_num < 0 || vector == NULL) {
		printf("ERROR: cannot free vector\n");
		return;
	}

	free(vector);
	vector = NULL;

	return;
}


void matrix_free_int(int **matrix, int row_num, int col_num) { 
	if(row_num <= 0 || col_num <= 0 || matrix == NULL) {
		printf("ERROR: cannot free matrix\n");
		return;
	}

	for(int i = 0; i < row_num; i++) {
		free(matrix[i]);
		matrix[i] = NULL;
	}
	free(matrix);
	matrix = NULL;

	return;
}

void matrix_free_char(char **matrix, int row_num, int col_num) { 
	if(row_num <= 0 || col_num <= 0 || matrix == NULL) {
		printf("ERROR: cannot free matrix\n");
		return;
	}

	for(int i = 0; i < row_num; i++) {
		free(matrix[i]);
		matrix[i] = NULL;
	}
	free(matrix);
	matrix = NULL;

	return;
}

void matrix_free_3D(int*** matrix, int row_num, int col_num) { 
	if(row_num <= 0 || col_num <= 0 || matrix == NULL) {
		printf("ERROR: cannot free matrix\n");
		return;
	}

	for(int i = 0; i < row_num; i++) {
        for (int j = 0; j < col_num; ++j){
            free(matrix[i][j]);
		}
        free(matrix[i]);
	}
	free(matrix);

	return;
}
