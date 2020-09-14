#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <limits.h>
#include "kmeans.h"
#include <math.h>

#define READ_ERROR_STRING "Errpr:\tFile was not in correct format.\n"

// Main Function
int main(int argc, char * argv[]) {
	// Start by reading the input from the command line prompt
	// In this k-means implementation, the program takes in 5 addition arguments:
	    //(1) number of cluster;
		//(2) maximum number of iteration time;
		//(3) minimum improvement rate used as a threshold to stop k-means;
		//(4) path of data file;
		//(5) path of result file;

	if (argc != 3) {
		print_command(argv[0]);
		return 1;
	}

	// This section will safely parse the value of k passed in to the program. If the argument cannot be parsed 
    // to an integer, or if it is larger than INT_MAX, we error out.
    char *endptr = NULL;
    int base = 10;
    errno = 0;
    long int long_k = strtol(argv[2], &endptr, base);

    // This will trigger if an error was encountered when trying to parse the input, or if the input was not a 
    // proper integer (e.g. 124A). This can also trigger if the input is too long to fit even in a long int.
    if((errno != 0) || (*endptr != '\0')) {
        fprintf(stderr, "The input: \"%s\" could not be parsed as an integer.\""
        " \n", argv[2]);
        return 1;
    }
        
    if((long_k > INT_MAX) || (long_k <= 0)) {
        fprintf(stderr, "The k-value input was:\t%ld\n"
        "K must be larger than zero, and no larger than %u.\n", long_k, INT_MAX);
        return 1;
    }

	// define input parameters:
	const char *file_name = argv[1];					// input file name
	int cluster_num = (int) long_k;						// number of clusters
	
	int iter_num = 40;	// max iteration nums
	double threshold = 0.2;			// threshold to stop 
	// const char *output_file = argv[5];					// output file


	// initialize:
	int data_num = 0;
	int dimension_num = 0;
	double ** data_matrix_origin = read_data(file_name, &data_num, &dimension_num);
	// TODO: normalize data
	double ** normalized_data_matrix = normalize_data(data_matrix_origin, data_num, dimension_num); // FIXME: something is wrong here

	double ** data_matrix = data_matrix_origin;
	// double ** data_matrix = normalized_data_matrix;
	// initialized centroid:
	// double ** centroid_matrix = initialize_centriods(data_matrix, cluster_num, data_num, dimension_num);
	double ** centroid_matrix = initialize_centriods_random(data_matrix, cluster_num, data_num, dimension_num); // TODO: 随机
	double ** distance_matrix = get_distance_matrix(data_matrix, centroid_matrix, cluster_num, data_num, dimension_num);
	int* cluster_vector = get_cluster_vector(distance_matrix, cluster_num, data_num);
	int* cluster_point_vector = get_cluster_points_number(data_matrix, cluster_vector, cluster_num, data_num);
	double RMS = root_mean_square(distance_matrix, cluster_vector, cluster_num, data_num);
	
	int iter = 0;
	double RMS_diff = -1;
	// begin training the data
	while(iter < iter_num) {
		printf(" ---------------------- %dth iteration --------------------\n", iter);
		update_centroids(data_matrix, centroid_matrix, cluster_vector, cluster_point_vector, cluster_num, data_num, dimension_num);
		distance_matrix = get_distance_matrix(data_matrix, centroid_matrix, cluster_num, data_num, dimension_num);
		cluster_vector = get_cluster_vector(distance_matrix, cluster_num, data_num);
		cluster_point_vector = get_cluster_points_number(data_matrix, cluster_vector, cluster_num, data_num);
		double new_RMS = root_mean_square(distance_matrix, cluster_vector, cluster_num, data_num);
		RMS_diff = (RMS - new_RMS) / RMS;
		printf("RMS_diff: %.2f", RMS_diff); // FIXME：改成打印完整结果
		if(RMS_diff <= threshold) { // FIXME: 换一种检查方式
			break;
		}
		iter++;
	}

	// write the result data used for knn to the output file
	// writeClusterResults(data_size, feature_size, output_file, data_matrix, cluster_label);

	// set all the spaces free
	matrix_free(data_matrix, data_num, dimension_num);
	return 1;
}
