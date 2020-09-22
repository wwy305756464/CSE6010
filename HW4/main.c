#include "search.h"

int main(int argc, char * argv[]) {

    // read in files (sub)
    const char *file_name = argv[1];
    int  matrix_size = 0;

    char** data_matrix = read_origin_data(file_name, &matrix_size); // n * n matrix store original data
    // printf("%c", data_matrix[0][2]);
    // data_matrix:
    // ? X ? ? ? ?
    // O ? ? ? ? ?
    // ? ? O ? X ?
    // ? X ? ? X O
    // ? ? ? ? ? O
    // ? ? ? O ? ?

    char char_O = 'O';
    char char_X = 'X';
    int count_O = 0;
    int count_X = 0;
    printf("get O\n");
    int** position_O = position_OX_func(data_matrix, char_O, &matrix_size, &count_O);
    printf("get X\n");
    int** position_X = position_OX_func(data_matrix, char_X, &matrix_size, &count_X);
    printf("count O and X: %d, %d \n", count_O, count_X);

    // position_O:
    // 1 0
    // 2 2
    // 3 5
    // 4 5
    // 5 3

    // position_X:
    // 0 1
    // 2 4
    // 3 1
    // 3 4

    // initialize 2D puzzle_matrix, all grids are 0
    int** puzzle_matrix = matrix_allocate_int(matrix_size, matrix_size); // 初始化了一个 n * n 的matrix，每个上面都是0
    // printf("%d", puzzle_matrix[0][0]);

    // initialize 3D domain_matrix, on each grid:
    //      domain[i][j][0] = 1 -> X
    //      domain[i][j][1] = 100 -> O
    int*** domain_matrix = matrix_allocate_3D(matrix_size, matrix_size);
    for(int i = 0; i < matrix_size; ++i){
        for (int j = 0; j < matrix_size; ++j){
            domain_matrix[i][j][0] = 1;
            domain_matrix[i][j][1] = 100;
        }
    }
    // domain_matrix:
    // [1][100] [1][100] [1][100] [1][100] [1][100] [1][100]
    // [1][100] [1][100] [1][100] [1][100] [1][100] [1][100]
    // [1][100] [1][100] [1][100] [1][100] [1][100] [1][100]
    // [1][100] [1][100] [1][100] [1][100] [1][100] [1][100]
    // [1][100] [1][100] [1][100] [1][100] [1][100] [1][100]
    // [1][100] [1][100] [1][100] [1][100] [1][100] [1][100]
    // printf("%d", domain_matrix[4][1][1]);  // 这里存在的问题是，如果超过size boundary，值会默认为0

    // 将 domain_matrix 已有的部分的domain改变
    modify_domain_matrix(domain_matrix, position_X, matrix_size, count_X, char_X);
    modify_domain_matrix(domain_matrix, position_O, matrix_size, count_O, char_O);
    printf("%d", domain_matrix[2][4][0]); 

    // domain_matrix after modification:
    // [1][100] [1][0]   [1][100] [1][100] [1][100] [1][100]
    // [0][100] [1][100] [1][100] [1][100] [1][100] [1][100]
    // [1][100] [1][100] [0][100] [1][100] [1][0]   [1][100]
    // [1][100] [1][0]   [1][100] [1][100] [1][0]   [0][100]
    // [1][100] [1][100] [1][100] [1][100] [1][100] [0][100]
    // [1][100] [1][100] [1][100] [0][100] [1][100] [1][100]
    
    int recur_r = 0;
    int recur_c = 0;
    int domain_index = 0;

    while(recur_r < matrix_size && recur_c < matrix_size){
        if (recur_r == 5) {
            break;
        }
        if (recur_c == matrix_size - 1){
            recur_c = 0;
            recur_r++;
        }

        int domain_number = domain_matrix[recur_r][recur_c][domain_index];
        domain_matrix[recur_r][recur_c][domain_index] = 0;
        puzzle_matrix[recur_r][recur_c] = domain_number;

        int* cur_row = vector_allocate(matrix_size);
        int* cur_col = vector_allocate(matrix_size);

        for (int c = 0; c < matrix_size; ++c) {
            cur_row[c] = puzzle_matrix[recur_r][c];
        }

        for (int r = 0; r < matrix_size; ++r) {
            cur_col[r] = puzzle_matrix[r][recur_c];
        }

        // bool check_cons_1_row = check_constraint_1(cur_row, matrix_size);
        // bool check_cons_1_col = check_constraint_1(cur_col, matrix_size);


        // recur_r++;
        ++recur_c;
        printf("%d, %d, loop \n", recur_c, recur_r);
    }



}