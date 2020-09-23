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


// check each row / col has same number of O and X
bool check_constraint_1(int* vector, int matrix_size){
    int sum = 0;
    for (int i = 0; i < matrix_size; ++i){
        sum += vector[i];
    }
    int num_of_X = sum % 100;
    int num_of_O = sum / 100;
    if ((num_of_X == matrix_size / 2) && (num_of_O == matrix_size / 2)){
        return true;
    }
    else{
        return false;
    }
}


// 检查每行/每列不能有超过两个连续的相同元素
bool check_constraint_2(int* vector, int matrix_size, int cur_index){
    if(vector[2] == 0){ // 如果当前行/列上元素个数小于3， 直接返回true
        return true;
    }

    // 检查当前数字和前一个数字是否相等，当前数字和前两个数字是否相等
    if((vector[cur_index] == vector[cur_index - 1]) && (vector[cur_index] == vector[cur_index - 2])) {
        return false;
    }

    return true;
}


bool check_constraint_3_row(int** puzzle_matrix, int r_num, int c_num, int matrix_size){
    if (c_num != 5) { // c = 5 的时候代表占满了这一行，如果当前行还没有占满，则不检查与之前行的关系，默认为true
        return true;
    }
    if (r_num == 0) { // 如果当前只便利到第一行，也默认是true
        return true;
    }

    int* current_row = vector_allocate(matrix_size);
    int** previous_rows = matrix_allocate_int(r_num, matrix_size); // r_num是index
    // int* previous_row = vector_allocate(matrix_size);

    for(int r = 0; r <= r_num; ++r){  // 这里r_num是index
        for(int c = 0; c < matrix_size; ++c){
            if (r == r_num){
                current_row[c] = puzzle_matrix[r][c];
            }
            else{
                previous_rows[r][c] = puzzle_matrix[r][c];
            }
        }
    } 
    // 到这里，比如遍历到了第四行的最后一个元素，进入这个判断函数，那么原始的puzzle matrix为：
    // [ 100 1   1   100 100 1   ]  -->  row0
    // [ 100 1   100 1   1   100 ]  -->  row1
    // [ 1   100 1   1   100 100 ]  -->  row2
    // [ 100 1   1   100 100 1   ]  -->  row3
    // 那么通过上面的，current_row 是 row3, previous_rows是row0, row1, row2
    // 我们需要依次比较row3和之前的所有row

    bool check_res = true;
    bool check_temp = true;
    for(int i = 0; i < r_num; ++i){
        check_temp = compare_array(current_row, previous_rows[i], matrix_size);
        if(check_temp == true){
            check_res = false;
            break;
        }
    }

    return check_res;
}


bool check_constraint_3_col(int** puzzle_matrix, int r_num, int c_num, int matrix_size){
    if (r_num != 5) { // r = 5 的时候代表占满了这一列，如果当前列还没有占满，则不检查与之前列的关系，默认为true
        return true;
    }
    if (c_num == 0) { // 如果当前只便利到第一列，也默认是true
        return true;
    }

    int* current_col = vector_allocate(matrix_size);
    int** previous_cols = matrix_allocate_int(c_num, matrix_size); // r_num是index
    // int* previous_row = vector_allocate(matrix_size);

    for(int c = 0; c <= c_num; ++c){  // 这里r_num是index
        for(int r = 0; r < matrix_size; ++r){
            if (c == c_num){
                current_col[r] = puzzle_matrix[r][c];
            }
            else{
                previous_cols[c][r] = puzzle_matrix[r][c];
            }
        }
    } 
    // 到这里，比如遍历到了第四行的最后一个元素，进入这个判断函数，那么原始的puzzle matrix为：
    // [ 100 1   1   100 100 1   ]  -->  row0
    // [ 100 1   100 1   1   100 ]  -->  row1
    // [ 1   100 1   1   100 100 ]  -->  row2
    // [ 100 1   1   100 100 1   ]  -->  row3
    // 那么通过上面的，current_row 是 row3, previous_rows是row0, row1, row2
    // 我们需要依次比较row3和之前的所有row

    bool check_res = true;
    bool check_temp = true;
    for(int i = 0; i < c_num; ++i){
        check_temp = compare_array(current_col, previous_cols[i], matrix_size);
        if(check_temp == true){
            check_res = false;
            break;
        }
    }

    return check_res;
}


bool compare_array(int* array1, int* array2, int n){  // 两个array完全相等返回true
    for (int i = 0; i < n; ++i){
        if (array1[i] != array2[i]) return false;
    }
    return true;
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

