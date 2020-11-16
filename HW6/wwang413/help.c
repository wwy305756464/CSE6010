#include "nn.h"

void Intial_Network(int** network, int numNeighbors){
    for(int i = 0; i < numAgents; ++i){
        for(int j = 0; j < numAgents; ++j){
            network[j][i] = numAgents;
        }
        int t = numNeighbors / 2;
        for(int range = t; range >= -t; --range){
            network[(i+ range + numAgents)%numAgents][i] = 1;
        }
        network[i][i] = 0;
    }
    return;
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

void Initial_SmallWord(int** network, double tp, int numNeighbors){
    if(tp == 0.0){
        return;
    }
    srand((unsigned)time(NULL));
    for(int t = 1; t <= numNeighbors/2; ++t){
        for(int i = t, j = 0; j < numAgents; ++j, ++i){
            if((double)rand()/RAND_MAX < tp){
                bool tag = true;
                while(tag == true){
                    int t_pos = rand() % numAgents;
                    if(network[t_pos][j] == numAgents){
                        network[j][t_pos] = 1;
                        network[t_pos][j] = network[j][t_pos];
                        //break;
                        tag = false;
                    }
                }
                network[(i + numAgents) % numAgents][j] = numAgents;
                network[j][(i + numAgents) % numAgents] = numAgents;
            }
        }
    }
    return;
}

void Update_Neighbor(int** network, double pInfection, double pRecovery, int* status, double pDisconnect){
    //srand((unsigned)time(NULL));
    int* tmp_status = vector_allocate(numAgents);
    for(int i = 0; i < numAgents; ++i){
        tmp_status[i] = status[i];
    }
    for(int i = 0; i < numAgents; ++i){
        if(status[i] == 1){
            double reratio = (double)rand()/RAND_MAX;
            if(reratio < pRecovery){
                tmp_status[i] = 2;
            }
        }
        for(int j = 0; j < numAgents; ++j){
            if(network[i][j] == 1){
                if(status[j] == 0 || status[j] == 2){
                    continue;
                }else if(status[j] == 1){
                    if(status[i] == 0){
                        double ifratio = (double)rand()/RAND_MAX;
                        if(ifratio < pInfection){
                            tmp_status[i] = 1;
                            Disconnect_Neighbor(network, pDisconnect, i, j);
                        }
                    }
                }
            }
        }
    }
    for(int m = 0; m < numAgents; ++m){
        status[m] = tmp_status[m];
    }
    return;
}

void Disconnect_Neighbor(int** network, double pDisconnect, int i, int j){
    if(pDisconnect == 0){
        return;
    }
    double disratio = (double)rand()/RAND_MAX;
    if(disratio < pDisconnect){
        network[i][j] = numAgents;
        network[j][i] = numAgents;
    }
    return;
}

int max(int a, int b){
    if(a > b){
        return a;
    }
    return b;
}