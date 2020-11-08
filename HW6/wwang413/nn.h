#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#define K 10
#define numAgents 500
#define P 0.25 //0.25
#define Pi 0.05
#define Pr 0.08
#define numIterations 100
#define Pd 0.5 //0.5

void Intial_Network(int** network, int numNeighbors);
int** matrix_allocate_int(int row_num, int col_num);
void Initial_SmallWord(int** network, double tp, int numNeighbors);
int* vector_allocate(int vector_num);
void Update_Neighbor(int** network, double pInfection, double pRecovery, int* status, double pDisconnect);
void Disconnect_Neighbor(int** network, double pDisconnect, int i, int j);
int max(int a, int b);



