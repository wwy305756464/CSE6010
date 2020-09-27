#include "search.h"

int main(int argc, char * argv[]) {

    // read in files (sub)
    const char *file_name = argv[1];
    int  matrix_size = 0;

    char** data_matrix = read_origin_data(file_name, &matrix_size); // n * n matrix store original data
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
    // printf("get O\n");
    int** position_O = position_OX_func(data_matrix, char_O, &matrix_size, &count_O);
    // printf("get X\n");
    int** position_X = position_OX_func(data_matrix, char_X, &matrix_size, &count_X);
    // printf("count O and X: %d, %d \n", count_O, count_X);

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
    int** puzzle_matrix = matrix_allocate_int(matrix_size+1, matrix_size+1); 

    // initialize 3D domain_matrix, on each grid:
    //      domain[i][j][0] = 1 -> X
    //      domain[i][j][1] = 100 -> O
    int*** domain_matrix = matrix_allocate_3D(matrix_size+1, matrix_size+1);
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

    
    // generate a copy of domain matrix 
    int*** domain_matrix_copy = matrix_allocate_3D(matrix_size+1, matrix_size+1);
    for(int i = 0; i < matrix_size; ++i){
        for (int j = 0; j < matrix_size; ++j){
            domain_matrix_copy[i][j][0] = 1;
            domain_matrix_copy[i][j][1] = 100;
        }
    }


    // modify domain matrix:
    //      if prefilled O -> [100][100]
    //      if prefilled X -> [1][1]
    modify_domain_matrix(domain_matrix, position_X, matrix_size, count_X, char_X);
    modify_domain_matrix(domain_matrix, position_O, matrix_size, count_O, char_O);

    // get a copy of original domain:
    modify_domain_matrix(domain_matrix_copy, position_X, matrix_size, count_X, char_X);
    modify_domain_matrix(domain_matrix_copy, position_O, matrix_size, count_O, char_O);
    // domain_matrix after modification:
    // [1][100] [1][0]   [1][100] [1][100] [1][100] [1][100]
    // [0][100] [1][100] [1][100] [1][100] [1][100] [1][100]
    // [1][100] [1][100] [0][100] [1][100] [1][0]   [1][100]
    // [1][100] [1][0]   [1][100] [1][100] [1][0]   [0][100]
    // [1][100] [1][100] [1][100] [1][100] [1][100] [0][100]
    // [1][100] [1][100] [1][100] [0][100] [1][100] [1][100]
    


    // start while loop: 
    int recur_r = 0; // current grid's row
    int recur_c = 0; // current grid's col
    int domain_index = 0; 
                          // domain index = 0 -> X
                          // domain index = 1 -> O
    int* cur_row = vector_allocate(matrix_size+1); // initialize cur-row and cur-col
    int* cur_col = vector_allocate(matrix_size+1);    
    int cnt = 0;
    while(recur_r < matrix_size && recur_c < matrix_size){
        // if(recur_r == matrix_size || recur_c == matrix_size){
        //     break;
        // }
        // printf("------------------------------while-----------------------------\n");

        int domain_number = domain_matrix[recur_r][recur_c][domain_index]; 

        domain_matrix[recur_r][recur_c][domain_index] = 0;  // pop element from domain
        puzzle_matrix[recur_r][recur_c] = domain_number;    // add element into puzzle

        // fill cur-row and cur-col
        for (int c = 0; c < matrix_size; ++c) {
            cur_row[c] = puzzle_matrix[recur_r][c];
        }

        for (int r = 0; r < matrix_size; ++r) {
            cur_col[r] = puzzle_matrix[r][recur_c];
        }

        // check constraints for cur row and col
        bool check_cons_1_row = check_constraint_1(cur_row, matrix_size);
        bool check_cons_1_col = check_constraint_1(cur_col, matrix_size);
        bool check_cons_2_row = check_constraint_2(cur_row, matrix_size, recur_c);  
        bool check_cons_2_col = check_constraint_2(cur_col, matrix_size, recur_r);
        bool check_cons_3_row = check_constraint_3_row(puzzle_matrix, recur_r, recur_c, matrix_size);
        bool check_cons_3_col = check_constraint_3_col(puzzle_matrix, recur_r, recur_c, matrix_size);


        // printf("check grid: %d, %d \n", recur_r, recur_c);
        // printf("current domain index: %d \n", domain_index);
        // printf("current grid domain: %d, %d \n", domain_matrix[recur_r][recur_c][0], domain_matrix[recur_r][recur_c][1]);
        // // printf("first row: %d, %d, %d, %d, %d, %d \n", cur_row[0], cur_row[1], cur_row[2], cur_row[3], cur_row[4], cur_row[5]);
        // // printf("previous row: %d, %d, %d, %d, %d, %d \n", prev_row[0], prev_row[1], prev_row[2], prev_row[3], prev_row[4], prev_row[5]);
        // printf("matrix: \n");
        // print_puzzle_result(puzzle_matrix, matrix_size);
        // printf("bool check: \ncons1 row: %d \ncons1 col: %d \n", check_cons_1_row, check_cons_1_col);
        // printf("cons2 row: %d \ncons2 col: %d \n", check_cons_2_row, check_cons_2_col);
        // printf("cons3 row: %d \ncons3 col: %d \n", check_cons_3_row, check_cons_3_col);

        // if all tests are passed 
        if (check_cons_1_row && check_cons_1_col && check_cons_2_row && check_cons_2_col && check_cons_3_row && check_cons_3_col){
            // if there is no elemnt left in domian, then recover the domain index
            if(domain_index == 1){
                domain_index = 0;
            }

            // if iterate to last element of the row:
            if (recur_c == matrix_size - 1){ 
                recur_c = 0;
                recur_r++;
            }
            // if not the last element of the row:
            else{
                recur_c++; 
            }
        }
        
        
        // if any of the tests does not passed:
        else{
            // if there is other number in current node's domain:
            if (domain_index == 0 && domain_matrix[recur_r][recur_c][1] != 0){
                puzzle_matrix[recur_r][recur_c] = 0;
                domain_index++;
                // printf("test false domain is not blank\n");
                continue; 
            }

            // if current grid's domain is blank, then backtrack to previous grid, and current 
            // grid's domain should be recovered to initial state. 
            bool checkblank = true;
            while (checkblank == true){
                puzzle_matrix[recur_r][recur_c] = 0;
                // if it is first element of the row, then should back to previous row
                if (recur_c == 0){
                    domain_matrix[recur_r][recur_c][0] = domain_matrix_copy[recur_r][recur_c][0];
                    domain_matrix[recur_r][recur_c][1] = domain_matrix_copy[recur_r][recur_c][1];
                    recur_c = matrix_size - 1;
                    recur_r--;

                }
                // if regular position
                else{
                    domain_matrix[recur_r][recur_c][0] = domain_matrix_copy[recur_r][recur_c][0];
                    domain_matrix[recur_r][recur_c][1] = domain_matrix_copy[recur_r][recur_c][1];
                    recur_c--;
                    
                    
                }
                // the backtracking should stop if reaches a grid whose domain is not blank
                if(domain_matrix[recur_r][recur_c][0] != 0 || domain_matrix[recur_r][recur_c][1] != 0){
                    // printf("check if false domain break\n");
                    checkblank = false;

                }
            }
        }
    }
    
    // substitute number matrix to char
    char** final_puzzle = substitude_to_OX(puzzle_matrix, matrix_size);
    print_puzzle_result(final_puzzle, matrix_size);

    // perform final test:
    bool check1 = final_check_constraint_1(final_puzzle, matrix_size);
    printf("Test 1: %d\n", check1);
    bool check2 = final_check_constraint_2(final_puzzle, matrix_size);
    printf("Test 2: %d\n", check2);
    bool check3 = final_check_constraint_3(final_puzzle, matrix_size);
    printf("Test 3: %d\n", check3);

    // freeup memory
    vector_free(cur_row, matrix_size);
    vector_free(cur_col, matrix_size);
    matrix_free_int(puzzle_matrix, matrix_size, matrix_size);
    matrix_free_int(position_X, matrix_size*matrix_size, 2);
    matrix_free_int(position_O, matrix_size*matrix_size, 2);
    matrix_free_char(data_matrix, matrix_size, matrix_size);
    matrix_free_3D(domain_matrix, matrix_size, matrix_size);
    matrix_free_3D(domain_matrix_copy, matrix_size, matrix_size);
    
    return 0;

}