#include "nn.h"

int network[numAgents][numAgents];

int main(int argc, char**argv){
    int numNeighbors = K;
    double pReplaceRandom = P;
    double pRecovery = Pr;
    double pInfection = Pi;
    double pDisconnect = Pd;
    if(numNeighbors & 1){
        numNeighbors += 1;
        printf("Waring, the numNeighbors is odd, has been added by 1\n");
    }
    if(numNeighbors > numAgents){
        numNeighbors = numAgents;
        printf("Waring, the numNeighbors exceeds population number, drop down to population\n");
    }
    if(pReplaceRandom > 1.0){
        pReplaceRandom = 1.0;
        printf("Waring, the probability of replacing random is bigger than 1, so reset to 1\n");
    }
    if(pReplaceRandom < 0.0){
        pReplaceRandom = 0.0;
        printf("Waring, the probability of replacing random is smaller than 0, so reset to 0\n");
    }
    if(pRecovery > 1.0){
        pRecovery = 1.0;
        printf("Waring, the probability of pRecovery is bigger than 1, so reset to 1\n");
    }
    if(pRecovery < 0.0){
        pRecovery = 0.0;
        printf("Waring, the probability of pRecovery is smaller than 0, so reset to 0\n");
    }
    if(pInfection > 1.0){
        pInfection = 1.0;
        printf("Waring, the probability of pInfection is bigger than 1, so reset to 1\n");
    }
    if(pInfection < 0.0){
        pInfection = 0.0;
        printf("Waring, the probability of pInfection is smaller than 0, so reset to 0\n");
    }
    if(pDisconnect > 1.0){
        pDisconnect = 1.0;
        printf("Waring, the probability of pDisconnect is bigger than 1, so reset to 1\n");
    }
    if(pDisconnect < 0.0){
        pDisconnect = 0.0;
        printf("Waring, the probability of pDisconnect is smaller than 0, so reset to 0\n");
    }

    int** network = matrix_allocate_int(numAgents, numAgents); 
    int** short_dis = matrix_allocate_int(numAgents, numAgents);

    Intial_Network(network, numNeighbors);
    Initial_SmallWord(network, pReplaceRandom, numNeighbors);

    //0 = susceptible, 1 = infected, 2 = recover
    int status[numAgents] = {0};
    status[0] = 1;

    int days = 0;
    int mxcnt = 0;
    int tagloop = 0;
    while(days++ < numIterations){
        int tmpcnt = 0;
        int s_cnt = 0;
        int r_cnt = 0;
        Update_Neighbor(network, pInfection, pRecovery, status, pDisconnect);
        for(int i = 0; i < numAgents; ++i){
            if(status[i] == 1){
                ++tmpcnt;
            }
            if(status[i] == 0){
                ++s_cnt;
            }
            if(status[i] == 2){
                ++r_cnt;
            }
        }
        //maximum number of infected individuals in a single iteration
        mxcnt = max(mxcnt, tmpcnt);
        //iteration number at which the maximum number of infected individuals occurs
        if(mxcnt == tmpcnt){
            tagloop = days;
        }

        //printf("day%d: s:%d, i:%d, r:%d \n", days, s_cnt, tmpcnt, r_cnt);


    }
    int ifcnt = 0, recnt = 0;
    for(int i = 0; i < numAgents; ++i){
        if(status[i] == 1){
            ++ifcnt;
        }
        if(status[i] == 2){
            ++recnt;
        }
    }

    printf("The maximum number of infected individuals in a single ietaration is %d \n", mxcnt);
    printf("The iteration number at which the maximum number of infected individuals occurs %d \n", tagloop);
    printf("The sum of the number of currently infectd and recovered individuals after the last iteration %d, %d \n", ifcnt, recnt);

    return 0;
    
}