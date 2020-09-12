#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include "kmeans.h"

#define READ_ERROR_STRING "Error:\tFile was not in correct format.\n"
#define USAGE_STRING "USAGE:./executableName input_file k_value"

int main(int argc, char** argv) {
    // argcs in this kmeans implemetation:
    // (1) program name
    // (2) input file name
    // (3) number of clusters
    // TODO: 看要不要加别的argc，比如 max iteration numbers 和 centroid difference to stop, 可能要改33行

    // nRows will hold how many rows of data there are, nCols holds the number of columns (attributes.) 
    // Do not change these variables. k will hold the value of k

    // passed in to the program from the command line.
    int nRows;
    int nCols; 
    int k;

/*
################################################################################
## Begininning of provided code to read in file
################################################################################
*/

// FIXME: 看能不能把 readin 这部分改成一个func
    // Here we check to be sure that the correct number of arguments have been passed in from the command 
    // line. The first argument is always the program name. If not, we print and error and return error status.
    printf("test success! \n");  //TODO: comment out

    // if(argc != 3){
    //     fprintf(stderr, "%s\nYou must pass your data file and k value "
    //     "(in that order)as an argument to this program.\n", USAGE_STRING);
    //     return 1;
    // }

    // // This section will safely parse the value of k passed in to the program. If the argument cannot be parsed 
    // // to an integer, or if it is larger than INT_MAX, we error out.
    // char *endptr = NULL;
    // int base = 10;
    // errno = 0;
    // long int long_k = strtol(argv[2], &endptr, base);

    // // This will trigger if an error was encountered when trying to parse the input, or if the input was not a 
    // // proper integer (e.g. 124A). This can also trigger if the input is too long to fit even in a long int.
    // if((errno != 0) || (*endptr != '\0')) {
    //     fprintf(stderr, "The input: \"%s\" could not be parsed as an integer.\""
    //     " \n", argv[2]);
    //     return 1;
    // }
        
    // if((long_k > INT_MAX) || (long_k <= 0)) {
    //     fprintf(stderr, "The k-value input was:\t%ld\n"
    //     "K must be larger than zero, and no larger than %u.\n", long_k, INT_MAX);
    //     return 1;
    // }

    // k = (int)long_k;

    // // This opens the file for reading. A return value of NULL indicates the file failed to open for some reason, 
    // // in which case we print out the error and return an error status.
    // FILE *infile = fopen(argv[1],"r");
    // if(infile == NULL) {
    //     fprintf(stderr, "Could not open the file:\t%s\n", argv[1]);
    //     perror("Failed to open file");
    //     return 2;
    // }

    // // This will read in the number of rows and columns (first line of the file). If it reads fewer than two 
    // // things, we know the file is incorrect.
    // int readIn = fscanf(infile, " %d %d", &nRows, &nCols); 

    // if(readIn != 2) {
    //     fprintf(stderr, READ_ERROR_STRING);
    //     fclose(infile);
    //     return 1;
    // }

    // // Makes a stack array with nRows rows and nCols columns.
    // // May be indexed with data_array[i][j].
    // double data_array[nRows][nCols];

    // // This loop reads in the expected number of rows and columns. If it fails to read the expected number, 
    // // it errors out. This doesn't catch some errors, E.G. too *many* lines in the input file, but you should 
    // // not be editing those files for the assignment anyway.
    // for (int i = 0; i < nRows; ++i) {
    //     for (int j = 0; j < nCols; ++j) {
    //         readIn = fscanf(infile," %lf", &(data_array[i][j]));
    //         // printf("%f\n", (data_array[i][j])); //TODO: comment out
    //         if(!readIn) {
    //             fprintf(stderr, READ_ERROR_STRING );
    //             return 1;
    //         }
    //     }
    // }

    // // Since we've read in all the data we need, close the file.
    // fclose(infile);

/*
################################################################################
## End of code provided for reading file.
################################################################################
*/

    /*

    IMPORTANT!

    Variables you will need, which *already exist* at this point in the
    code!

    nRows: an int containing the number of rows (items) in the dataset
    nCols:  an int containing the number of columns(attributes per item).
    k:  an int containing the value of 'k' (number of clusters) passed to the program from the command line.

    data_array: a 2-dimensional double array which is nRows x nCols.
        This may be indexed like data_array[i][j], where i is a row index and j is a column index.

    */

    // define and initialized parameters:
    // int nRows;
    // int nCols; 
    // int k;
    const char * file_name = argv[1];
    int data_num = 0;
    int dimension_num = 0;


    // read in data

    printf("checkpoint");

    double ** data_array = read_data(file_name, &data_num, &dimension_num);

    // double ** centroids = matrix_allocate(k, nCols);

    // initialize centroids
    // printf("initialize_centroids");
    // initialize_centroids(k, nCols, nRows, data_array, centroids);


    // freeup all used memories
    // matrix_freeup(k, nCols, centroids);




    return 0;
}

// #include <stdio.h>
// #include <stdlib.h>
// #include "kmeans.h"

// int main() {
//     // basic settings
//     // n - data size
//     // d - data dimension
//     // k - cluster number

//     // reading from input file, 生成 n * k 的数组

//     // normalized read-in data

//     // assign k centroids:
//     // 1. by seletcing first k points as centriods
//     // 2. by randomly selecting k points from the dataset

//     // call kmeans()
//     // 传入

//     // write to output file

//     // free memory
// }